// This file is part of the PiEMU Project
// Licensing information can be found in the LICENSE file
// (C) 2014 Nandor Licker. All rights reserved.
#include "common.h"


// -----------------------------------------------------------------------------
static inline void ADD(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "addl   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void AND(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "andl   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void EOR(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "xorl   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void LSL(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "shll   %%cl, %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [D] "+g" (d)
    : [S] "c"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void LSR(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "shrl   %%cl, %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [D] "+g" (d)
    : [S] "c"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void ASR(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "sarl   %%cl, %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [D] "+g" (d)
    : [S] "c"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void ADC(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movb   %[C], %%al       \n\t"
      "addb   $0xFF, %[C]      \n\t"
      "adcl   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "+m" (t->c)
    , [V] "=m" (t->v)
    , [D] "+g" (d)
    : [S] "r"  (s)
    : "memory", "cc", "al"
    );
}


// -----------------------------------------------------------------------------
static inline void SBC(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movb   %[C], %%al       \n\t"
      "subb   $0x01, %%al      \n\t"
      "sbbl   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setnc  %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "+m" (t->c)
    , [V] "=m" (t->v)
    , [D] "+g" (d)
    : [S] "r"  (s)
    : "memory", "cc", "al"
    );
}


// -----------------------------------------------------------------------------
static inline void ROR(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "rorl   %%cl, %[D]       \n\t"
      "setc   %[C]             \n\t"
      "testl  %[D], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [D] "+r" (d)
    : [S] "c"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void TST(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "testl  %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void NEG(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[S], %[D]       \n\t"
      "negl   %[D]             \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc", "eax"
    );
}


// -----------------------------------------------------------------------------
static inline void CMP(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[S], %%eax      \n\t"
      "cmpl   %%eax, %[D]      \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setnc  %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    : [D] "g"  (d)
    , [S] "g"  (s)
    : "memory", "cc", "eax"
    );
}


// -----------------------------------------------------------------------------
static inline void CMN(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[D], %%eax      \n\t"
      "addl   %[S], %%eax      \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    : [D] "g"  (d)
    , [S] "g"  (s)
    : "memory", "cc", "eax"
    );
}


// -----------------------------------------------------------------------------
static inline void ORR(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "orl    %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void MUL(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "imul   %[S], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+r" (d)
    : [S] "g"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void BIC(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[S], %%eax      \n\t"
      "notl   %%eax            \n\t"
      "andl   %%eax, %[D]      \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "+g" (d)
    : [S] "g"  (s)
    : "memory", "cc", "eax"
    );
}


// -----------------------------------------------------------------------------
static inline void MVN(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[S], %[D]       \n\t"
      "notl   %[D]             \n\t"
      "test   %[D], %[D]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "=r" (d)
    : [S] "r"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void MOV(ARMState *t, int32_t &d, int32_t s)
{
  asm volatile
    ( "movl   %[S], %[D]       \n\t"
      "test   %[S], %[S]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [D] "=g" (d)
    : [S] "r"  (s)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void LSL(ARMState *t, int32_t &r, int32_t a, int32_t b)
{
  asm volatile
    ( "shll   %%cl, %[A]       \n\t"
      "movl   %[A], %[R]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [R] "=g" (r)
    : [A] "r"  (a)
    , [B] "c"  (b)
    : "memory", "cc", "eax"
    );
}


// -----------------------------------------------------------------------------
static inline void LSR(ARMState *t, int32_t &r, int32_t a, int32_t b)
{
  asm volatile
    ( "shrl   %%cl, %[A]       \n\t"
      "movl   %[A], %[R]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [R] "=g" (r)
    : [A] "r"  (a)
    , [B] "c"  (b)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void ASR(ARMState *t, int32_t &r, int32_t a, int32_t b)
{
  asm volatile
    ( "sarl   %%cl, %[A]       \n\t"
      "movl   %[A], %[R]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [R] "=g" (r)
    : [A] "r"  (a)
    , [B] "c"  (b)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void ADD(ARMState *t, int32_t &r, int32_t a, int32_t b)
{
  asm volatile
    ( "addl   %[A], %[B]       \n\t"
      "movl   %[B], %[R]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setc   %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    , [R] "=g" (r)
    : [A] "g"  (a)
    , [B] "r"  (b)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void SUB(ARMState *t, int32_t &r, int32_t a, int32_t b)
{
  asm volatile
    ( "subl   %[A], %[B]       \n\t"
      "movl   %[B], %[R]       \n\t"
      "sets   %[N]             \n\t"
      "setz   %[Z]             \n\t"
      "setnc  %[C]             \n\t"
      "seto   %[V]             \n\t"
    : [N] "=m" (t->n)
    , [Z] "=m" (t->z)
    , [C] "=m" (t->c)
    , [V] "=m" (t->v)
    , [R] "=g" (r)
    : [A] "g"  (a)
    , [B] "r"  (b)
    : "memory", "cc"
    );
}


// -----------------------------------------------------------------------------
static inline void LDR(ARMState *t, int32_t &r, uint32_t addr)
{
  r = t->mem->ReadLong(addr);
}


// -----------------------------------------------------------------------------
static inline void STR(ARMState*, int32_t&, uint32_t)
{
  assert(!"STR");
}


// -----------------------------------------------------------------------------
static inline void LDRB(ARMState*, int32_t&, uint32_t)
{
  assert(!"LDRB");
}


// -----------------------------------------------------------------------------
static inline void STRB(ARMState*, int32_t&, uint32_t)
{
  assert(!"STRB");
}


// -----------------------------------------------------------------------------
static inline void LDRH(ARMState*, int32_t&, uint32_t)
{
  assert(!"LDRH");
}


// -----------------------------------------------------------------------------
static inline void STRH(ARMState*, int32_t&, uint32_t)
{
  assert(!"STRH");
}


// -----------------------------------------------------------------------------
static inline void LDSB(ARMState*, int32_t&, uint32_t)
{
  assert(!"LDSB");
}


// -----------------------------------------------------------------------------
static inline void LDSH(ARMState*, int32_t&, uint32_t)
{
  assert(!"LDSH");
}


// -----------------------------------------------------------------------------
static inline void STMIA(ARMState*, int32_t&, uint8_t)
{
  assert(!"STMIA");
}


// -----------------------------------------------------------------------------
static inline void LDMIA(ARMState*, int32_t&, uint8_t)
{
  assert(!"LDMIA");
}


// -----------------------------------------------------------------------------
static void SWI(ARMState* t)
{
  t->exc = ARM_EXC_SWI;
}


// -----------------------------------------------------------------------------
static void UND(ARMState* t)
{
  t->exc = ARM_EXC_UND;
}


// -----------------------------------------------------------------------------
void ThumbExecute(ARMState *t)
{
  register uint32_t flags;
  register uint16_t op;
  register int32_t *r;
  int32_t off;
  uint32_t temp;

  r = t->r;
  while (!t->hang)
  {
    // Check whether we need to swith to THUMB or jazelle
    // This meas that either J got set and we switch to Jazelle
    // or T is no longer set and we switch to ARM
    if (t->j || !t->t)
    {
      return;
    }


    // Read the instruction from memory and increment the program
    // counter. In order to account for the pipelining effect,
    // the program counter must be always greater by 4.
    op = t->mem->ReadInstrWord(t->pc);
    t->pc += 4;


    // Check for exceptions. Interrupts are usually handled in ARM
    // state, so we must exit the THUMB interpreter loop and return
    // to the ARM one to handle interrupts.
    switch (t->exc)
    {
      case ARM_EXC_NONE:
      {
        break;
      }
      case ARM_EXC_UND:
      {
        t->hang = 1;
        return;
      }
      case ARM_EXC_SWI:
      {
        t->hang = 1;
        return;
      }
    }


    // Decode the instructions. The most significant 7 bits should
    // be enough to distinguish most instrucitions, but additional
    // switch statements are required for some categories such as
    // ALU operations and miscellaneous instructions. We try to
    // keep the number of cases low (< 256) so compilers generate
    // a jump table instead of binary search
    switch (op >> 9)
    {
      // LSL Rd, Rs, #Imm5
      case 0x00 ... 0x03:
      {
        LSL(t, r[op & 7], r[(op >> 3) & 7], (op >> 6) & 31);
        break;
      }

      // LSR Rd, Rs, #Imm5
      case 0x04 ... 0x07:
      {
        LSR(t, r[op & 7], r[(op >> 3) & 7], (op >> 6) & 31);
        break;
      }

      // ASR Rd, Rs, #Imm5
      case 0x08 ... 0x0B:
      {
        ASR(t, r[op & 7], r[(op >> 3) & 7], (op >> 6) & 31);
        break;
      }

      // ADD Rd, $s, Rn
      case 0x0C:
      {
        ADD(t, r[op & 7], r[(op >> 6) & 7], r[(op >> 3) & 7]);
        break;
      }

      // SUB Rd, Rs, Rn
      case 0x0D:
      {
        SUB(t, r[op & 7], r[(op >> 6) & 7], r[(op >> 3) & 7]);
        break;
      }

      // ADD Rd, Rs, #Imm3
      case 0x0E:
      {
        ADD(t, r[op & 7], (op >> 6) & 7, r[(op >> 3) & 7]);
        break;
      }

      // SUB Rd, Rs, #Imm3
      case 0x0F:
      {
        SUB(t, r[op & 7], (op >> 6) & 7, r[(op >> 3) & 7]);
        break;
      }

      // MOV Rd, #Imm8
      case 0x10 ... 0x13:
      {
        MOV(t, r[(op >> 8) & 7], op & 0xFF);
        break;
      }

      // CMP Rd, #Imm8
      case 0x14 ... 0x17:
      {
        CMP(t, r[(op >> 8) & 7], op & 0xFF);
        break;
      }

      // ADD Rd, #Imm8
      case 0x18 ... 0x1B:
      {
        ADD(t, r[(op >> 8) & 7], op & 0xFF, r[(op >> 8) & 7]);
        break;
      }

      // SUB Rd, #Imm8
      case 0x1C ... 0x1F:
      {
        SUB(t, r[(op >> 8) & 7], op & 0xFF, r[(op >> 8) & 7]);
        break;
      }

      // alu Rd, Rs
      case 0x20 ... 0x21:
      {
        switch ((op >> 6) & 0xF)
        {
          case 0x0: AND(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x1: EOR(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x2: LSL(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x3: LSR(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x4: ASR(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x5: ADC(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x6: SBC(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x7: ROR(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x8: TST(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0x9: NEG(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xA: CMP(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xB: CMN(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xC: ORR(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xD: MUL(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xE: BIC(t, r[op & 7], r[(op >> 3) & 7]); break;
          case 0xF: MVN(t, r[op & 7], r[(op >> 3) & 7]); break;
          default:
          {
            /* LCOV_EXCL_LINE */ __builtin_unreachable();
          }
        }

        break;
      }

      case 0x22 ... 0x23:
      {
        switch ((op >> 6) & 0xF)
        {
          // ADD Rd/Hd, Rs/Hs
          case 0x0: UND(t); break;
          case 0x1: ADD(t, r[0 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;
          case 0x2: ADD(t, r[8 + (op & 7)], r[0 + ((op >> 3) & 7)]); break;
          case 0x3: ADD(t, r[8 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;

          // CMP Rd/Hd, Rs/Hs
          case 0x4: UND(t); break;
          case 0x5: CMP(t, r[0 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;
          case 0x6: CMP(t, r[8 + (op & 7)], r[0 + ((op >> 3) & 7)]); break;
          case 0x7: CMP(t, r[8 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;

          // MOV Rd/Hd, Rs/Hs
          case 0x8: UND(t); break;
          case 0x9: MOV(t, r[0 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;
          case 0xA: MOV(t, r[8 + (op & 7)], r[0 + ((op >> 3) & 7)]); break;
          case 0xB: MOV(t, r[8 + (op & 7)], r[8 + ((op >> 3) & 7)]); break;

          // BX
          case 0xC: case 0xD:
          {
            t->pc = t->r[(op >> 3) & 7];
            t->t = t->pc & 1;
            t->pc &= ~1;
            continue;
          }

          // BLX
          case 0xE: case 0xF:
          {
            continue;
          }

          default:
          {
            /* LCOV_EXCL_LINE */ __builtin_unreachable();
          }
        }

        break;
      }

      // LDR  Rn, [PC + #Imm10]
      case 0x24 ... 0x27:
      {
        LDR(t, r[(op >> 8) & 7], (t->pc & ~2) + ((op & 0xFF) << 2));
        break;
      }

      // STR Rd, [Rn + Ro]
      case 0x28:
      {
        STR(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // STRH Rd, [Rn + Ro]
      case 0x29:
      {
        STRH(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // STRB Rd, [Rn + Ro]
      case 0x2A:
      {
        STRB(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // LDRH Rd, [Rn + Ro]
      case 0x2B:
      {
        LDRH(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // LDR Rd, [Rn + Ro]
      case 0x2C:
      {
        LDR(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // LSDB Rd, [Rn + Ro]
      case 0x2D:
      {
        LDSB(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // LDRB  Rd, [Rn + Ro]
      case 0x2E:
      {
        LDRB(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // LDSH Rd, [Rn + Ro]
      case 0x2F:
      {
        LDSH(t, r[op & 7], r[(op >> 3) & 7] + r[(op >> 6) & 7]);
        break;
      }

      // STR Rd, [Rn + #Imm7]
      case 0x30 ... 0x33:
      {
        STR(t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6 << 2) & 0x7F));
        break;
      }

      // LDR Rd, [Rn + #Imm7]
      case 0x34 ... 0x37:
      {
        LDR(t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6 << 2) & 0x7F));
        break;
      }

      // STRB Rd, [Rn + #Imm5]
      case 0x38 ... 0x3B:
      {
        STRB(t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6) & 0x1F));
        break;
      }

      // LDRB Rd, [Rn + #Imm5]
      case 0x3C ... 0x3F:
      {
        LDRB (t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6) & 0x1F));
        break;
      }

      // STRH Rd, [Rn + #Imm6]
      case 0x40 ... 0x43:
      {
        STRH (t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6 << 1) & 0x3F));
        break;
      }

      // LDRH Rd, [Rn + #Imm6]
      case 0x44 ... 0x47:
      {
        LDRH (t, r[op & 7], r[(op >> 3) & 7] + ((op >> 6 << 1) & 0x3F));
        break;
      }

      // STR Rd, [SP + #Imm10]
      case 0x48 ... 0x4B:
      {
        STR(t, r[(op >> 8) & 7], t->sp + ((op & 0xFF) << 2));
        break;
      }

      // LDR Rd, [SP + #Imm10]
      case 0x4C ... 0x4F:
      {
        LDR(t, r[(op >> 8) & 7], t->sp + ((op & 0xFF) << 2));
        break;
      }

      // Add Rd, Pc, #Imm10
      case 0x50 ... 0x53:
      {
        r[(op >> 8) & 3] = (t->pc & ~2) + ((op & 0xFF) << 2);
        break;
      }

      // Add Rd, Sp, #Imm10
      case 0x54 ... 0x57:
      {
        r[(op >> 8) & 3] = t->sp + ((op & 0xFF) << 2);
        break;
      }

      // Miscellaneous
      case 0x58 ... 0x5F:
      {
        switch ((op >> 5) & 0x7F)
        {
          // ADD SP, SP, #Imm9
          case 0x00 ... 0x03:
          {
            t->sp += (op & 0x7F) << 2;
            break;
          }

          // SUB SP, SP, #Imm9
          case 0x04 ... 0x07:
          {
            t->sp -= (op & 0x7F) << 2;
            break;
          }

          // SXTH
          case 0x10 ... 0x11:
          {
            t->r[op & 7] = (int32_t)((int16_t)t->r[(op >> 3) & 7]);
            break;
          }

          // SXTB
          case 0x12 ... 0x13:
          {
            t->r[op & 7] = (int32_t)((int8_t)t->r[(op >> 3) & 7]);
            break;
          }

          // UXTH
          case 0x14 ... 0x15:
          {
            t->r[op & 7] = (uint32_t)((uint16_t)t->r[(op >> 3) & 7]);
            break;
          }

          // UXTB
          case 0x16 ... 0x17:
          {
            t->r[op & 7] = (uint32_t)((uint8_t)t->r[(op >> 3) & 7]);
            break;
          }

          // PUSH
          case 0x20 ... 0x2F:
          {
            assert(!"PUSH");
            break;
          }

          // CPS
          case 0x33:
          {
            assert(!"CPS");
            break;
          }

          // REV
          case 0x50 ... 0x51:
          {
            t->r[op & 7] = BSWAP_32(t->r[(op >> 3) & 7]);
            break;
          }

          // REV16
          case 0x52 ... 0x53:
          {
            temp = t->r[(op >> 3) & 7];
            t->r[op & 7] = (((temp >> 24) & 0xFF) << 16) |
                           (((temp >> 16) & 0xFF) << 24) |
                           (((temp >>  8) & 0xFF) <<  0) |
                           (((temp >>  0) & 0xFF) <<  8);
            break;
          }

          // REVSH
          case 0x56 ... 0x57:
          {
            t->r[op & 7] = (int32_t)((int16_t)BSWAP_16(t->r[(op >> 3) & 7]));
            break;
          }

          // POP
          case 0x60 ... 0x6F:
          {
            assert(!"POP");
            break;
          }

          // BKPT
          case 0x70 ... 0x77:
          {
            t->hang = 1;
            break;
          }

          case 0x78 ... 0x7F:
          {
            if (op & 0xF)
            {
              // IT
              assert(!"IT");
              break;
            }

            switch ((op >> 4) & 0xF)
            {
              // NOP
              case 0x0:
              {
                assert(!"NOP");
                break;
              }

              // YIELD
              case 0x1:
              {
                assert(!"YIELD");
                break;
              }

              // WFE
              case 0x2:
              {
                assert(!"WFE");
                break;
              }

              // WFI
              case 0x3:
              {
                assert(!"WFI");
                break;
              }

              // SEV
              case 0x4:
              {
                assert(!"SEV");
                break;
              }
            }
          }

          // UND
          default:
          {
            UND(t);
            break;
          }
        }

        break;
      }

      // STMIA Rn!, { Rlist }
      case 0x60 ... 0x63:
      {
        STMIA(t, r[(op >> 8) & 7], op & 0xFF);
        break;
      }

      // LDMIA Rn!, { Rlist }
      case 0x64 ... 0x67:
      {
        LDMIA(t, r[(op >> 8) & 7], op & 0xFF);
        break;
      }

      // Bcc label
      case 0x68 ... 0x6E:
      {
        // Sign extend offset & adjust for pipelining
        if ((off = (op & 0xFF)) & 0x80)
        {
          off |= ~0xFF;
        }
        off <<= 1;

        // Check condition
        switch ((op >> 8) & 0xF)
        {
          case 0x0: temp = t->z;                  break;
          case 0x1: temp = !t->z;                 break;
          case 0x2: temp = t->c;                  break;
          case 0x3: temp = !t->c;                 break;
          case 0x4: temp = t->n;                  break;
          case 0x5: temp = !t->n;                 break;
          case 0x6: temp = t->v;                  break;
          case 0x7: temp = !t->v;                 break;
          case 0x8: temp = t->c && !t->z;         break;
          case 0x9: temp = !t->c || t->z;         break;
          case 0xA: temp = t->n == t->v;          break;
          case 0xB: temp = t->n != t->v;          break;
          case 0xC: temp = !t->z && t->n == t->v; break;
          case 0xD: temp = t->z || t->n != t->v;  break;
          default:
          {
            /* LCOV_EXCL_LINE */ __builtin_unreachable();
          }
        }

        // Adjust PC
        t->pc += temp ? off : (-2);
        continue;
      }

      // SWI | UND
      case 0x6F:
      {
        (*(((op >> 8) & 0x1) ? SWI : UND)) (t);
        break;
      }

      // B label
      case 0x70 ... 0x73:
      {
        if ((off = (op & 0x7FF)) & 0x80)
        {
          off |= ~0x7FF;
        }

        t->pc += off << 1;
        continue;
      }

      // THUMB2
      case 0x74 ... 0x77:
      {
        assert(!"THUMB2");
        break;
      }

      // BL label
      case 0x78 ... 0x7B:
      {
        assert(!"BLO");
        break;
      }

      // BL label
      case 0x7C ... 0x7F:
      {
        assert(!"BLH");
        break;
      }

      default:
      {
        /* LCOV_EXCL_LINE */ __builtin_unreachable();
      }
    }

    // By subtracting two here and adding 4 on the next
    // iteration, we keep PC correctly adjusted and
    // still fetch the correct instruction
    t->pc -= 2;
  }
}
