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

/**
 @Summary
    Represents the INPUT kind of a peripheral
 */
#define INPUT 0
/**
 @Summary
    Represents the OUTPUT kind of a peripheral
 */
#define OUTPUT 1

/**
 @Summary
    For PPS Input modules, placeholder for the <code>code</code> field which is unused
 */
#define NONE 0xFFu

/**
 @Summary
    The struct represents a PPS peripheral of the MCU
 @Description
    According to the MCU PPS structure, not every pin is mappable with every
    PPS peripheral. Instead, each group of 5 pins is mappable to a predetermined
    set of inputs and outputs. In order not to risk to initialize a wrong peripheral
    on a pin, each peripheral is defined as a struct containing, together with its
    code, information about its role and even the PPS register. When packet into pps
    groups, everything becomes restricted.
 @Remarks
    Follows the description of every field of the struct.
    <li>
        <ul><code>const unsigned char code</code> :code for PPS output</ul>
        <ul><code>const unsigned char io</code> : flag marker for input/output</ul>
        <ul><code>const unsigned int *const *input_pps</code> : pointer to PPS input register </ul>
    </li>
 */
typedef struct{
    const unsigned char code;
    const unsigned char io;
    volatile unsigned int *input_pps;
} peripheral;

typedef const peripheral* pps_block[16];

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
    volatile unsigned int *tris;
    volatile unsigned int *lat;
    volatile unsigned int *port;
    volatile unsigned int *odc;
    volatile unsigned int *cnen;
    volatile unsigned int *cnstat;
    volatile unsigned int *cnpu;
    volatile unsigned int *cnpd;
    volatile unsigned int *cncon;
    volatile unsigned int *clr;
    volatile unsigned int *inv;
    volatile unsigned int *set;
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
        <ul><code>volatile unsigned int *const *output_pps</code> : this is a pointer
            to the PPS Output register that must be manipulated in order to map an output
            on this pin. </ul>
        <ul><code>const pps_block *const *pps</code> : pointer to the pps_block associated </ul>
    </li>
 */
typedef struct{
    const io_port *io;
    const unsigned int mask;
    volatile unsigned int *output_pps;
    const pps_block *pps;
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

extern const peripheral INT1;
extern const peripheral INT2;
extern const peripheral INT3;
extern const peripheral INT4;
extern const peripheral T2CK;
extern const peripheral T3CK;
extern const peripheral T4CK;
extern const peripheral T5CK;
extern const peripheral IC1;
extern const peripheral IC2;
extern const peripheral IC3;
extern const peripheral IC4;
extern const peripheral IC5;
extern const peripheral OC1;
extern const peripheral OC2;
extern const peripheral OC3;
extern const peripheral OC4;
extern const peripheral OC5;
extern const peripheral REFCLKI;
extern const peripheral REFCLKO;
extern const peripheral U1CTS;
extern const peripheral U1RTS;
extern const peripheral U1RX;
extern const peripheral U1TX;
extern const peripheral U2CTS;
extern const peripheral U2RTS;
extern const peripheral U2RX;
extern const peripheral U2TX;
extern const peripheral SDI1;
extern const peripheral SDO1;
extern const peripheral SS1;
extern const peripheral SDI2;
extern const peripheral SDO2;
extern const peripheral SS2;
extern const peripheral OCFA;
extern const peripheral OCFB;
extern const peripheral C1OUT;
extern const peripheral C2OUT;
extern const peripheral C3OUT;

extern const pps_block GROUP1;
extern const pps_block GROUP2;
extern const pps_block GROUP3;
extern const pps_block GROUP4;


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
