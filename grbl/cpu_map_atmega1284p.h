/*
  cpu_map_atmega1284p.h - Pin mapping for ATmega1284P
  Target board: Creality v1.1.4 (Melzi / Sanguinololu compatible)

  Sanguino Arduino digital pin -> AVR port/bit mapping:
    D0  = PB0   D8  = PD0   D16 = PC0   D24 = PA7
    D1  = PB1   D9  = PD1   D17 = PC1   D25 = PA6
    D2  = PB2   D10 = PD2   D18 = PC2   D26 = PA5
    D3  = PB3   D11 = PD3   D19 = PC3   D27 = PA4
    D4  = PB4   D12 = PD4   D20 = PC4   D28 = PA3
    D5  = PB5   D13 = PD5   D21 = PC5   D29 = PA2
    D6  = PB6   D14 = PD6   D22 = PC6   D30 = PA1
    D7  = PB7   D15 = PD7   D23 = PC7   D31 = PA0

  Creality v1.1.4 / Melzi stepper pin assignments:
    X_STEP  = D15 (PD7)    X_DIR  = D21 (PC5)
    Y_STEP  = D22 (PC6)    Y_DIR  = D23 (PC7)
    Z_STEP  = D3  (PB3)    Z_DIR  = D2  (PB2)
    ENABLE  = D14 (PD6) -- shared for X and Y
    Z_ENABLE= D26 (PA5) -- separate for Z
    X_LIMIT = D18 (PC2), Y_LIMIT = D19 (PC3), Z_LIMIT = D20 (PC4)
    PROBE   = D17 (PC1)

  NOTE: Step pins are on 3 different ports (PD, PC, PB).
  The GRBL_1284P_MULTIPORT define activates multi-port step/dir
  handling in stepper.c.
*/

#ifndef CPU_MAP_ATMEGA1284P_H
#define CPU_MAP_ATMEGA1284P_H

#ifdef CPU_MAP_ATMEGA1284P

// -----------------------------------------------------------------------
// Serial
// -----------------------------------------------------------------------
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// -----------------------------------------------------------------------
// Step pulse pins  (3 ports => use GRBL_1284P_MULTIPORT in stepper.c)
// -----------------------------------------------------------------------
#define GRBL_1284P_MULTIPORT // enables multi-port step/dir code in stepper.c

// X Step: PD7
#define X_STEP_DDR DDRD
#define X_STEP_PORT PORTD
#define X_STEP_BIT 7
#define X_STEP_MASK (1 << X_STEP_BIT)

// Y Step: PC6
#define Y_STEP_DDR DDRC
#define Y_STEP_PORT PORTC
#define Y_STEP_BIT 6
#define Y_STEP_MASK (1 << Y_STEP_BIT)

// Z Step: PB3
#define Z_STEP_DDR DDRB
#define Z_STEP_PORT PORTB
#define Z_STEP_BIT 3
#define Z_STEP_MASK (1 << Z_STEP_BIT)

// Convenience mask for init
#define STEP_MASK                                                              \
  (X_STEP_MASK | Y_STEP_MASK |                                                 \
   Z_STEP_MASK) // This is only valid if same port, but we use it for DDR init

// -----------------------------------------------------------------------
// Direction pins
// -----------------------------------------------------------------------
// X Dir: PC5
#define X_DIR_DDR DDRC
#define X_DIR_PORT PORTC
#define X_DIRECTION_BIT 5
#define X_DIR_MASK (1 << X_DIRECTION_BIT)

// Y Dir: PC7
#define Y_DIR_DDR DDRC
#define Y_DIR_PORT PORTC
#define Y_DIRECTION_BIT 7
#define Y_DIR_MASK (1 << Y_DIRECTION_BIT)

// Z Dir: PB2
#define Z_DIR_DDR DDRB
#define Z_DIR_PORT PORTB
#define Z_DIRECTION_BIT 2
#define Z_DIR_MASK (1 << Z_DIRECTION_BIT)

// -----------------------------------------------------------------------
// Stepper enable
// -----------------------------------------------------------------------
// XY Enable: PD6 (Active LOW)
#define STEPPERS_DISABLE_DDR DDRD
#define STEPPERS_DISABLE_PORT PORTD
#define STEPPERS_DISABLE_BIT 6
#define STEPPERS_DISABLE_MASK (1 << STEPPERS_DISABLE_BIT)

// Z Enable: PA5 (Active LOW)
#define Z_ENABLE_DDR DDRA
#define Z_ENABLE_PORT PORTA
#define Z_ENABLE_BIT 5
#define Z_ENABLE_MASK (1 << Z_ENABLE_BIT)

// -----------------------------------------------------------------------
// Limit switches  -- all on PORTC
//   X=PC2, Y=PC3, Z=PC4
// -----------------------------------------------------------------------
#define LIMIT_DDR DDRC
#define LIMIT_PIN PINC
#define LIMIT_PORT PORTC
#define X_LIMIT_BIT 2
#define Y_LIMIT_BIT 3
#define Z_LIMIT_BIT 4
#define LIMIT_MASK                                                             \
  ((1 << X_LIMIT_BIT) | (1 << Y_LIMIT_BIT) | (1 << Z_LIMIT_BIT))

#define LIMIT_INT PCIE2
#define LIMIT_INT_vect PCINT2_vect
#define LIMIT_PCMSK PCMSK2

// -----------------------------------------------------------------------
// Control pins (cycle start / feed hold / reset)
// Using PORTA (PA0-PA2)
// -----------------------------------------------------------------------
#define CONTROL_DDR DDRA
#define CONTROL_PIN PINA
#define CONTROL_PORT PORTA
#define CONTROL_RESET_BIT 0       // PA0
#define CONTROL_FEED_HOLD_BIT 1   // PA1
#define CONTROL_CYCLE_START_BIT 2 // PA2
#define CONTROL_INT PCIE0         // PCINT0 group = PORTA
#define CONTROL_INT_vect PCINT0_vect
#define CONTROL_PCMSK PCMSK0
#define CONTROL_MASK                                                           \
  ((1 << CONTROL_RESET_BIT) | (1 << CONTROL_FEED_HOLD_BIT) |                   \
   (1 << CONTROL_CYCLE_START_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK

// -----------------------------------------------------------------------
// Probe pin (Mapped to Z-Limit PC4)
// -----------------------------------------------------------------------
#define PROBE_DDR DDRC
#define PROBE_PIN PINC
#define PROBE_PORT PORTC
#define PROBE_BIT 4
#define PROBE_MASK (1 << PROBE_BIT)

// -----------------------------------------------------------------------
// Coolant Control
// -----------------------------------------------------------------------
#define COOLANT_FLOOD_DDR DDRB
#define COOLANT_FLOOD_PORT PORTB
#define COOLANT_FLOOD_BIT 4 // Creality v1.1.4 Controllable Fan (PB4)

// MIST is not used on this board, keeping placeholder
#define COOLANT_MIST_DDR DDRC
#define COOLANT_MIST_PORT PORTC
#define COOLANT_MIST_BIT 4 // Dummy placeholder

// -----------------------------------------------------------------------
// Spindle Options (Digital PA7 enable, PA6 direction)
// -----------------------------------------------------------------------
#define SPINDLE_ENABLE_DDR DDRA
#define SPINDLE_ENABLE_PORT PORTA
#define SPINDLE_ENABLE_BIT 7

#define SPINDLE_DIRECTION_DDR DDRA
#define SPINDLE_DIRECTION_PORT PORTA
#define SPINDLE_DIRECTION_BIT 1

// -----------------------------------------------------------------------
// Variable Spindle (PWM) Definitions
// To satisfy compiler, using Timer 2 even if pins conflict.
// -----------------------------------------------------------------------
#define SPINDLE_PWM_MAX_VALUE 255
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE 1
#endif
#define SPINDLE_PWM_OFF_VALUE 0
#define SPINDLE_PWM_RANGE (SPINDLE_PWM_MAX_VALUE - SPINDLE_PWM_MIN_VALUE)

#define SPINDLE_TCCRA_REGISTER TCCR2A
#define SPINDLE_TCCRB_REGISTER TCCR2B
#define SPINDLE_OCR_REGISTER OCR2A
#define SPINDLE_COMB_BIT COM2A1

#define SPINDLE_TCCRA_INIT_MASK ((1 << WGM20) | (1 << WGM21))
#define SPINDLE_TCCRB_INIT_MASK (1 << CS22)

#define SPINDLE_PWM_DDR DDRA
#define SPINDLE_PWM_PORT PORTA
#define SPINDLE_PWM_BIT 4 // Dummy mapping to PA4 to avoid PD7 conflict

// -----------------------------------------------------------------------
// Generic Stepper Definitions (to satisfy setup code)
// -----------------------------------------------------------------------
#define STEP_MASK (X_STEP_MASK | Y_STEP_MASK | Z_STEP_MASK)
#define DIRECTION_MASK (X_DIR_MASK | Y_DIR_MASK | Z_DIR_MASK)

// These are required by non-multiport guarded code
#ifndef GRBL_1284P_MULTIPORT
#define STEP_PORT PORTD
#define STEP_DDR DDRD
#define DIRECTION_PORT PORTD
#define DIRECTION_DDR DDRD
#endif

#endif // CPU_MAP_ATMEGA1284P
#endif // CPU_MAP_ATMEGA1284P_H
