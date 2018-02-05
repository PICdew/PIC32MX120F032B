#ifndef _DIGITAL_IO_H
#define _DIGITAL_IO_H

/**
 @Summary
    Represents the logical ON state of a pin (1)
 */
#define ON 1
/**
 @Summary
    Represents the logical OFF state of a pin (0)
 */
#define OFF 0
/**
 @Summary
    Represents the logical HIGH state of a pin (1)
 */
#define HIGH 1
/**
 @Summary
    Represents the logical LOW state of a pin (0)
 */
#define LOW 0


/*
 * Even though it seems impossible, in this MCU
 * there are limited groups of pins which are
 * mappable to limited groups of inputs and limited
 * groups of pins that can map to limited groups of
 * outputs. In order to make this passage as easy and
 * error-free as possible to the developer, it is
 * necessary to find a safe but light way to map
 * every pin to a set of peripheral input and a set
 * of peripheral output. Luckily, at least, those pin
 * groups are fixed. Accordingly, input and output 
 * peripherals will be mapped in a constant struct which
 * will be pointed by the pin.
 */

/* Indexes for Input Group 1 */
#define INT4        0b0000
#define T2CK        0b0001
#define IC4         0b0010
#define SS1         0b0011
#define REFCLKI     0b0100

/* Indexes for Input Group 2 */
#define INT3        0b0001
#define T3CK        0b0010
#define IC3         0b0011
#define U1CTS       0b0100
#define U2RX        0b0101
#define SDI1        0b0110

/* Indexes for Input Group 3 */
#define INT2        0b0001
#define T4CK        0b0010
#define IC1         0b0011
#define IC5         0b0100
#define U1RX        0b0101
#define U2CTS       0b0110
#define SDI2        0b0111
#define OCFB        0b1000

/* Indexes for Input Group 4 */
#define INT1        0b0001
#define T5CK        0b0010
#define IC2         0b0011
#define SS2         0b0100
#define OCFA        0b0101

#define NO_CONNECT  0b0000
/* Indexes for the Output Group 1 */
#define U1TX        0b0001
#define U2RTS       0b0010
#define SS1         0b0011
#define OC1         0b0101
#define C2OUT       0b0111

/* Indexes for the Output Group 2 */
#define SDO1        0b0011
#define SDO2        0b0100
#define OC2         0b0101
#define C3OUT       0b0111

/* Indexes for the Output Group 3 */
//#define SDO1      0b0011 //already defined
//#define SDO2      0b0100 //already defined
#define OC4         0b0101
#define OC5         0b0110
#define REFCLKO     0b0111

/* Indexes for the Output Group 4 */
#define U1RTS       0b0001
#define U2TX        0b0010
#define SS2         0b0100
#define OC3         0b0101
#define C1OUT       0b0111


/**
  @Summary
    The struct represents an IO port of the MCU

  @Description
    An IO Port struct contains pointers to any register involved in manipulation
    of a particular IO port. In the PIC32MX model, there are many
    registers related to the IO management, and the access to any of those is
    necessary in order to work on IO ports at best. Every register pointer is
    declared volatile *const, avoiding unintentional modifies of the pointer values.
 
  @Remarks
    Here are the specifications of every register pointer:
    <li>
        <ul><code>volatile unsigned int *const *tris</code> : pointer to the TRIS register. It is responsible
            for the Tri-State, involved in pin role switching between input and output </ul>
        <ul><code>volatile unsigned int *const *lat</code> : pointer to the LAT register. This is responsible
            for digital writes on output pins. </ul>
        <ul><code>volatile unsigned int *const *port</code> : pointer to the PORT register. It is responsible
            for the read operations. Any write operation on this register will affect
            latches anyway.</ul>
        <ul><code>volatile unsigned int *const *odc</code> : pointer to the ODC register. The Open-Drain Configuration
            allows the user to manage a pin as open-drain, allowing it to output
            voltages higher than the MCU Vdd when an external pull-up is correctly
            positioned, limited to the Vih of the MCU</ul>
        <ul><code>volatile unsigned int *const *cnen</code> : pointer to the CNEN register. The Change Notification
            Enable register allows the MCU to trigger an interrupt on variation of
            singular pins.</ul>
        <ul><code>volatile unsigned int *const *cnstat</code> : pointer to the CNSTAT register. This register
            is read-only and changes whenever a pin of the port changes its state.</ul>
        <ul><code>volatile unsigned int *const *cnpu</code> : pointer to the CNPU register. Writes on this register
            enable/disable internal weak pull-ups for MCU's pins of the port.</ul>
        <ul><code>volatile unsigned int *const *cnpd</code> : pointer to the CNPD register. Writes on this register
            enable/disable internal weak pull-down for MCU's pins of the port. </ul>
        <ul><code>volatile unsigned int *const *cncon</code> : pointer to the CNCON register. </ul>
        <ul><code>volatile unsigned int *const *clr</code> : pointer to the CLR register. This write-only register
            is a shortcut for atomic pin clear operations on a port. After a write 
            on this register, every high bit clears the associated pin </ul>
        <ul><code>volatile unsigned int *const *inv</code> : pointer to INV register. This write-only register,
            when written, inverts the state of every output pin associated with
            high bits of the register written </ul>
        <ul><code>volatile unsigned int *const *set</code> : pointer to the SET register. This write-only register
            allows atomic bit set operations. After a write on the register, every 
            output pin associated to high bits of the register is set high </ul>
    </li>
 */
typedef struct{
    volatile unsigned int *const *tris;
    volatile unsigned int *const *lat;
    volatile unsigned int *const *port;
    volatile unsigned int *const *odc;
    volatile unsigned int *const *cnen;
    volatile unsigned int *const *cnstat;
    volatile unsigned int *const *cnpu;
    volatile unsigned int *const *cnpd;
    volatile unsigned int *const *cncon;
    volatile unsigned int *const *clr;
    volatile unsigned int *const *inv;
    volatile unsigned int *const *set;
}io_port;

/**
 @Summary
    The struct represents a single digital pin of the MCU.
 @Description
    In order to allow the maximum flexibility for any IO operation, every pin
    requires a strong set of informations. Those involves IO port registers,
    masks for pin setting, value to set on input_pps registers and pointer to
    the output PPS register. For the PIC32MX series, Peripheral Pin Select (PPS)
    allows remapping of digital peripherals only (UART, SPI, CAN, ...).
    <b>PPS is allowed only if CFGCON<13> = 0 </b>. <br/>
        Not all peripherals can be mapped freely to all pins.
 @Remarks
    Follows the description of every field of the struct.
    <li>
        <ul><code>volatile io_port *const *io</code> : pointer to an io_port. The io_port struct contains
            pointers to every useful i/o register. This workaround allows the
            library to allocate only one io_port struct for every port and point
            to it instead of duplicating registers on every pin struct. Delcared
            as volatile *const, avoiding unintentional modifications and access issues.</ul>
        <ul><code>const unsigned int mask</code> : this represents the mask value for
            the peculiar pin. This value identifies which bit of the registers must be
            manipulated in order to work on the pin itself. </ul>
        <ul><code>const unsigned char input_pps</code> : this is the value that must be
            loaded into an input PPS register in order to map this pin on it. </ul>
        <ul><code>volatile unsigned int *const *output_pps</code> : this is a pointer
            to the PPS Output register that must be manipulated in order to map an output
            on this pin. </ul>
    </li>
 */

typedef struct{
    volatile io_port *const *io;
    const unsigned int mask;
    const unsigned char input_pps;
    volatile unsigned int *const *output_pps;
} pin;


extern const io_port RA;
extern const io_port RB;

extern const pin RA0;
extern const pin RA1;
extern const pin RA2;
extern const pin RA3;
extern const pin RA4;

extern const pin RB0;
extern const pin RB1;
extern const pin RB2;
extern const pin RB3;
extern const pin RB4;
extern const pin RB5;
extern const pin RB6;
extern const pin RB7;
extern const pin RB8;
extern const pin RB9;
extern const pin RB10;
extern const pin RB11;
extern const pin RB12;
extern const pin RB13;
extern const pin RB14;
extern const pin RB15;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    
    int ExampleFunction(int param1, int param2);


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
