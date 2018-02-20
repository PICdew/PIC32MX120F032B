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
#define INPUT 1
/**
 @Summary
    Represents the OUTPUT kind of a peripheral
 */
#define OUTPUT 0

/**
 @Summary
    For PPS Input modules, placeholder for the <code>code</code> field which is unused
*/
#define NONE 0xFFu

/**
 @Summary
    For Analog/Digital selection function, represents the DIGITAL selection
 */
#define DIGITAL 0

/**
 @Summary
    For Analog/Digital selection function, represents the ANALOGIC selection
 */
#define ANALOGIC 1

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
    <ul>
        <li><code>const unsigned char output_pps_code</code> :code for PPS output</li>
        <li><code>const unsigned char io</code> : flag marker for input/output</li>
        <li><code>const unsigned int *const *input_pps</code> : pointer to PPS input register </li>
    </ul>
 */
typedef struct{
    const unsigned char output_pps_code;
    const unsigned char io;
    volatile unsigned int *input_pps;
} peripheral;

typedef const volatile peripheral* pps_block[16];

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
    <ul>
        <li><code>volatile unsigned int *const *tris</code> : pointer to the TRIS register. It is responsible
            for the Tri-State, involved in pin role switching between input and output </li>
        <li><code>volatile unsigned int *const *lat</code> : pointer to the LAT register. This is responsible
            for digital writes on output pins. </li>
        <li><code>volatile unsigned int *const *port</code> : pointer to the PORT register. It is responsible
            for the read operations. Any write operation on this register will affect
            latches anyway.</li>
        <li><code>volatile unsigned int *const *odc</code> : pointer to the ODC register. The Open-Drain Configuration
            allows the user to manage a pin as open-drain, allowing it to output
            voltages higher than the MCU Vdd when an external pull-up is correctly
            positioned, limited to the Vih of the MCU</li>
        <li><code>volatile unsigned int *const *cnen</code> : pointer to the CNEN register. The Change Notification
            Enable register allows the MCU to trigger an interrupt on variation of
            singular pins.</li>
        <li><code>volatile unsigned int *const *cnstat</code> : pointer to the CNSTAT register. This register
            is read-only and changes whenever a pin of the port changes its state.</li>
        <li><code>volatile unsigned int *const *cnpu</code> : pointer to the CNPU register. Writes on this register
            enable/disable internal weak pull-ups for MCU's pins of the port.</li>
        <li><code>volatile unsigned int *const *cnpd</code> : pointer to the CNPD register. Writes on this register
            enable/disable internal weak pull-down for MCU's pins of the port. </li>
        <li><code>volatile unsigned int *const *cncon</code> : pointer to the CNCON register. </li>
        <li><code>volatile unsigned int *const *clr</code> : pointer to the CLR register. This write-only register
            is a shortcut for atomic pin clear operations on a port. After a write 
            on this register, every high bit clears the associated pin </li>
        <li><code>volatile unsigned int *const *inv</code> : pointer to INV register. This write-only register,
            when written, inverts the state of every output pin associated with
            high bits of the register written </li>
        <li><code>volatile unsigned int *const *set</code> : pointer to the SET register. This write-only register
            allows atomic bit set operations. After a write on the register, every 
            output pin associated to high bits of the register is set high </li>
    </ul>
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
    <ul>
        <li><code>volatile io_port *const *io</code> : pointer to an io_port. The io_port struct contains
            pointers to every useful i/o register. This workaround allows the
            library to allocate only one io_port struct for every port and point
            to it instead of duplicating registers on every pin struct. Delcared
            as volatile *const, avoiding unintentional modifications and access issues.</li>
        <li><code>const unsigned int mask</code> : this represents the mask value for
            the peculiar pin. This value identifies which bit of the registers must be
            manipulated in order to work on the pin itself. </li>
        <li><code>volatile unsigned int *const *output_pps</code> : this is a pointer
            to the PPS Output register that must be manipulated in order to map an output
            on this pin. </li>
        <li><code>const pps_block *const *pps</code> : pointer to the pps_block associated </li>
    </ul>
 */
typedef struct{
    const volatile io_port *io;
    const unsigned int mask;
    volatile unsigned int *output_pps;
    const volatile pps_block *pps;
    const unsigned char pps_input_code;
} pin;

/**
 @Summary
    The struct represents an arbitrary group of pin
 @Description
    It's used to determine peculiar groups (like 5v tolerant pins, analog pins, etc...)
 */
typedef const volatile pin* pin_group[16];


extern const volatile io_port RA;
extern const volatile io_port RB;

extern const volatile pin RA0;
extern const volatile pin RA1;
extern const volatile pin RA2;
extern const volatile pin RA3;
extern const volatile pin RA4;

extern const volatile pin RB0;
extern const volatile pin RB1;
extern const volatile pin RB2;
extern const volatile pin RB3;
extern const volatile pin RB4;
extern const volatile pin RB5;
extern const volatile pin RB6;
extern const volatile pin RB7;
extern const volatile pin RB8;
extern const volatile pin RB9;
extern const volatile pin RB10;
extern const volatile pin RB11;
extern const volatile pin RB12;
extern const volatile pin RB13;
extern const volatile pin RB14;
extern const volatile pin RB15;

extern const volatile peripheral INT1;
extern const volatile peripheral INT2;
extern const volatile peripheral INT3;
extern const volatile peripheral INT4;
extern const volatile peripheral T2CK;
extern const volatile peripheral T3CK;
extern const volatile peripheral T4CK;
extern const volatile peripheral T5CK;
extern const volatile peripheral IC1;
extern const volatile peripheral IC2;
extern const volatile peripheral IC3;
extern const volatile peripheral IC4;
extern const volatile peripheral IC5;
extern const volatile peripheral OC1;
extern const volatile peripheral OC2;
extern const volatile peripheral OC3;
extern const volatile peripheral OC4;
extern const volatile peripheral OC5;
extern const volatile peripheral REFCLKI;
extern const volatile peripheral REFCLKO;
extern const volatile peripheral U1CTS;
extern const volatile peripheral U1RTS;
extern const volatile peripheral U1RX;
extern const volatile peripheral U1TX;
extern const volatile peripheral U2CTS;
extern const volatile peripheral U2RTS;
extern const volatile peripheral U2RX;
extern const volatile peripheral U2TX;
extern const volatile peripheral SDI1;
extern const volatile peripheral SDO1;
extern const volatile peripheral SS1;
extern const volatile peripheral SDI2;
extern const volatile peripheral SDO2;
extern const volatile peripheral SS2;
extern const volatile peripheral OCFA;
extern const volatile peripheral OCFB;
extern const volatile peripheral C1OUT;
extern const volatile peripheral C2OUT;
extern const volatile peripheral C3OUT;

extern const volatile pps_block GROUP1;
extern const volatile pps_block GROUP2;
extern const volatile pps_block GROUP3;
extern const volatile pps_block GROUP4;

/**
@Function
  inline void pin_set_direction(const pin *p, unsigned char direction)

@Summary
    The fuction sets a digital pin as input or output

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves the request in 2 cycles.
    The code interacts with the TRISx register associated to the pin.

@Precondition
    None.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

  @param direction Desired direction, which can be INPUT or OUTPUT

@Example
    @code
    pin_set_direction(&RB4, INPUT); //sets RB4 pin as input (TRISB<5> = 1)
    pin_set_direction(&RA3, OUTPUT); //sets RA3 pin as output (TRISA<4> = 0)
*/
extern inline void pin_set_direction(const volatile pin *p, unsigned char direction);

/**
@Function
  inline void pin_set_output_state(const pin *p, unsigned char value)

@Summary
    The fuction sets the output of a digital pin (HIGH or LOW)

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves in 2 cycles due to
    conditional controls. For a fast, 1 cycle access use 
    <code>pin_set_output_high(const pin *p)</code> or <code>pin_set_output_low(const pin *p)</code>
    instead. For multiple access to different pins, use 
    <code>port_set_output_state(const io_port *p. unsigned int mask)</code>.
    The function affects the content of LATx register.

@Precondition
    Required pin must be already set as OUTPUT; otherwise, port won't be written

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

  @param value Desired output value, which can be HIGH or LOW (ON or OFF are accepted too)

@Example
    @code
    pin_set_output_state(&RB4, HIGH); //sets RB4 pin high (LATB<5> = 1)
    pin_set_output_state(&RA3, LOW); //sets RA3 pin low (LATA<4> = 0)
*/
extern inline void pin_set_output_state(const volatile pin *p, unsigned char value);

/**
@Function
  inline void pin_set_output_high(const pin *p)

@Summary
    The fuction drives the requested pin HIGH

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves inline in 1 cycle,
    consequentially not affecting temporized operations.
    The code interacts with the LATx register associated to the pin.

@Precondition
    The pin must be set as OUTPUT; otherwise operation will be ignored

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

@Example
    @code
    pin_set_output_high(&RB3); //drives RB3 HIGH (LATB<4> = 1)
*/
extern inline void pin_set_output_high(const volatile pin *p);

/**
@Function
  inline void pin_set_output_low(const pin *p)

@Summary
    The fuction drives the requested pin LOW

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves inline in 1 cycle,
    consequentially not affecting temporized operations.
    The code interacts with the LATx register associated to the pin.

@Precondition
    The pin must be set as OUTPUT; otherwise operation will be ignored

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

@Example
    @code
    pin_set_output_low(&RB3); //drives RB3 LOW (LATB<4> = 0)
*/
extern inline void pin_set_output_low(const volatile pin *p);

/**
@Function
  inline void pin_invert(const pin *p)

@Summary
    The function inverts the current output state of the pin

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves inline in 1 cycle,
    consequentially not affecting temporized operations.
    The code interacts with the LATxINV register associated to the pin.

@Precondition
    The pin must be set as OUTPUT; otherwise operation will be ignored

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

@Example
    @code
    pin_set_output_high(&RB3); //drives RB3 HIGH (LATB<4> = 1)
    pin_invert(&RB3);          //inverts RB3 to LOW (LATBINV<4> = 1)
*/
extern inline void pin_invert(const volatile pin *p);

/**
@Function
  inline unsigned char pin_read(const pin *p)

@Summary
    The function returns the current value of the digital pin

@Description
    The advantage of using a function to set the pin over the register access
    heavily helps code clearance. The function resolves inline in 1 cycle,
    consequentially not affecting temporized operations.
    The code interacts with the LATxINV register associated to the pin.

@Precondition
    None.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins

@Example
    @code
    pin_set_output_high(&RB3); //drives RB3 HIGH (LATB<4> = 1)
    pin_invert(&RB3);          //inverts RB3 to LOW (LATBINV<4> = 1)
*/
extern inline unsigned char pin_read(const volatile pin *p);

/**
@Function
  unsigned char pin_assign_peripheral(const pin *p, peripheral *peripheral)

@Summary
    The function assigns the given peripheral to the given pin if possible.

@Description
    The function hides the underneath terrifying register structure for PPS.
    The main issue about it is the fact that not every peripheral can be
    mapped to any remappable pin. 4 groups of 5 pins each can be mapped to
    four arbitrary groups of IOs defined by the datasheet through a really
    intricate SFRs assignment system.
    This function not only hides the different procedures for input or output
    assignment but it detects whether an assignment is legal or not.

@Precondition
    None.

@Returns
<ul>
    <li><code>1</code> if the assignment is legal and done</li>
    <li><code>0</code> if the assignment is not legal and no action was taken</li>
</ul>
 
@Parameters
    @param p A <code>const *pin</code> from the available pins
    @param peripheral The pointer of an available peripheral between the defined ones

@Remarks
    A limited set of digital peripheral pins cannot be mapped to RP. This includes
    SPI clock sources (SCK1 fixed on pin 22, SCK2 fixed on pin 23),
    external Interrupt 0 source (fixed on pin 13) and the entire I2C module
    (SCL on pin 14, SDA on pin 15).

@Example
    @code
    pin_assign_peripheral(&RB3, &REFCLKI); //assigns REFCLKI peripheral to RB3, returns 1
    pin_assign_peripheral(&RB4, &INT3);    //fails the assignment due to illegal pairing, returns 0
*/
extern unsigned char pin_assign_peripheral(const volatile pin *p, const volatile peripheral *peripheral);

/**
@Function
  inline unsigned char pin_open_drain_selection(const pin *p, unsigned char request)

@Summary
    The function turns ON or OFF Open Drain function for the required pin
    according to <code>request</code> value, if the pin is 5V tolerant.

@Description
    The function resolves the request in 2 cycles. There's no faster alternative
    on this library for this operation; anyway this is not expected to be called
    so often nor to be a 1 cycle operation. The functions interacts with ODCx register

@Precondition
    In order to activate Open Drain on a pin, the pin must be set as OUTPUT.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins
  @param request the Open Drain selection (ON or OFF)

@Returns
<ul>
    <li><code>1</code> if the assignment is legal and done (pin is 5V-tolerant)</li>
    <li><code>0</code> if the assignment is not legal and no operation has been done </li>
</ul>
@Remarks
    Only a couple of pins are 5V-tolerant, precisely from RB5 to RB11 
 
@Example
    @code
    pin_open_drain_selection(&RB5, ON); //set RA0 as Open Drain, returns 1
    pin_open_drain_selection(&RB7, OFF);//set RB4 as digital, returns 1
    pin_open_drain_selection(&RA0, OFF);//does nothing and returns 0 (pin not 5V-tolerant)
*/
extern inline unsigned char pin_open_drain_selection(const volatile pin *p, unsigned char request);

/**
@Function
    inline unsigned char pin_select_working_mode(const pin *p, unsigned char analog_digital)

@Summary
    The function sets the given pin as DIGITAL or ANALOGIC, but only if the pin is
    one of the analog set.

@Description
    The function interacts with ANSELx register.

@Precondition
    None.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins
  @param analog_digital the pin selection between ANALOGIC and DIGITAL

@Returns
<ul>
    <li><code>1</code> if the association is legal and has been committed</li>
    <li><code>0</code> if the association is not legal and no operation was instantiated</li>
</ul>

@Remarks
    The only available analogic peripheral is ADC, so you probably want to set
    the pin as input before switching to ANALOGIC. The only analog pins available are:
    <ul>
        <li>RA0, RA1 as AN0, AN1</li>
        <li>RB0 to RB3 as AN2 to AN5</li>
        <li>RB12, RB13 as AN12, AN11</li>
        <li>RB15 as AN9</li>
    </ul>
 
@Example
    @code
    pin_select_working_mode(&RA0, ANALOGIC); //set RA0 as analogic, returns 1
    pin_select_working_mode(&RB3, DIGITAL);//set RB3 as digital, returns 1
    pin_select_working_mode(&RA2, DIGITAL);//does nothing, return 0
*/
extern inline unsigned char pin_select_working_mode(const volatile pin *p, unsigned char analog_digital);

/**
@Function
    inline void pin_assign_interrupt_on_change(const pin *p, unsigned char activated, unsigned char stop_in_idle)

@Summary
    The function turns ON or OFF the Interrupt On Change function for the selected
    pin, together with the chance of turning it ON or OFF during Idle.

@Description
    The function interacts with CNENx register.

@Precondition
    If desired, behaviour in Idle should be set with <code>

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins
  @param activated can be ON if activation of Interrupt On Change is required, OFF otherwise

@Remarks
    Global Interrupt Enable must be active in order to make Interrupt-On-Change work. When
    <code>activated</code> is OFF, <code>stop_in_idle</code> is DNC
 
@Example
    @code
    pin_assign_interrupt_on_change(&RA0, ON); //set Interrupt on change on RA0
    pin_assign_interrupt_on_change(&RB3, ON);  //set Interrupt on change on RB3
    
*/
extern inline void pin_assign_interrupt_on_change(const volatile pin *p, unsigned char activated);

/**
@Function
    inline void pin_assign_pull_up(const pin *p, unsigned char activated)

@Summary
    The function turns ON or OFF the internal weak pull-up.

@Description
    The function interacts with CNPUx register.

@Precondition
    None.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins
  @param activated can be ON if activation of Internal Weak Pull-up is required, OFF otherwise

@Remarks
    Even with Open Drain active, internal pull-up still pulls to Vdd; activating
    weak pull-up on an externally pulled-up line may result in driver damage.
    Internal pull-up tecnically does not pull at Vdd, but approximately ad Vdd - 0.7V
 
@Example
    @code
    pin_assign_pull_up(&RA0, ON); //activates internal pull-up on RA0
    pin_assign_pull_up(&RB3, OFF);//deactivates internal pull-up on RB3
*/
extern inline void pin_assign_pull_up(const volatile pin *p, unsigned char activated);

/**
@Function
    inline void pin_assign_pull_down(const pin *p, unsigned char activated)

@Summary
    The function turns ON or OFF the internal weak pull-down.

@Description
    The function interacts with CNPDx register.

@Precondition
    None.

@Parameters
  @param p A <code>const *pin</code> from the available and defined pins
  @param activated can be ON if activation of Internal Pull-down is required, OFF otherwise

@Remarks
    Even with Open Drain active, internal pull-up still pulls to Vdd; activating
    weak pull-up on an externally pulled-up line may result in driver damage.
    Internal pull-up tecnically does not pull at Vdd, but approximately ad Vdd - 0.7V
 
@Example
    @code
    pin_assign_pull_down(&RA0, ON); //activates internal pull-down on RA0
    pin_assign_pull_down(&RB3, OFF);//deactivates internal pull-down on RB3
*/
extern inline void pin_assign_pull_down(const volatile pin *p, unsigned char activated);

/**
@Function
    inline void port_set_direction(const io_port *p, unsigned int mask)

@Summary
    The function sets up the direction of each pin of the port according to the mask

@Description
    The function works as proxy for the TRIS assignment, but it makes the code
    easier to understand

@Precondition
    None.

@Parameters
  @param p A <code>const *io_port</code> from the available and defined ports (RA, RB)
  @param mask the mask to be written on the register
 
@Example
    @code
    port_set_direction(&RA, 0b11111); //sets entire Port A as Input
*/
extern inline void port_set_direction(const volatile io_port *p, unsigned int mask);

/**
@Function
    inline void port_set_output_state(const io_port *p, unsigned int mask)

@Summary
    The function sets up the output value of each pin of the port according to the mask

@Description
    The function works as proxy for the LAT assignment, but it makes the code
    easier to understand

@Precondition
    None.

@Parameters
  @param p A <code>const *io_port</code> from the available and defined ports (RA, RB)
  @param mask the mask to be written on the register
 
@Example
    @code
    port_set_output_state(&RA, 0b11111); //sets entire Port A output as HIGH
*/
extern inline void port_set_output_state(const volatile io_port *p, unsigned int mask);

/**
@Function
    inline void port_invert(const io_port *p)

@Summary
    The function inverts the state of every selected pin of the port

@Description
    The function works as proxy for the LATxINV assignment, but it makes the code
    easier to understand

@Precondition
    None.

@Parameters
  @param p A <code>const *io_port</code> from the available and defined ports (RA, RB)
  @param mask the mask to be written on the register
 
@Example
    @code
    port_invert(&RA, 0b11111); //inverts entire Port A output as HIGH
*/
extern inline void port_invert(const volatile io_port *p, unsigned char mask);

/**
@Function
    inline void port_set_change_notice_behaviour(const io_port *p, unsigned char active, unsigned char stop_in_idle)

@Summary
    The function sets the working mode for the Interrupt On Change module for
    IO ports.

@Description
    The function works as proxy for the CNSTATx assignment, but it makes the code
    easier to understand

@Precondition
    None.

@Parameters
  @param p A <code>const *io_port</code> from the available and defined ports (RA, RB)
  @param active sets whether the module should be ON or OFF
  @param idle_state sets whether the module should be ON or OFF during Sleep/Idle
 
@Example
    @code
    port_set_change_notice_behaviour(&RA, ON, OFF); //sets the Int. on change ON but OFF in idle
*/
extern void port_set_change_notice_behaviour(const volatile io_port *p, unsigned char active, unsigned char idle_state);

#endif