#include <xc.h>
#include "digital_io.h"

const peripheral INT1 =     { NONE, INPUT, &INT1R } ;
const peripheral INT2 =     { NONE, INPUT, &INT2R } ;
const peripheral INT3 =     { NONE, INPUT, &INT3R } ;
const peripheral INT4 =     { NONE, INPUT, &INT4R } ;
const peripheral T2CK =     { NONE, INPUT, &T2CKR } ;
const peripheral T3CK =     { NONE, INPUT, &T3CKR } ;
const peripheral T4CK =     { NONE, INPUT, &T4CKR } ;
const peripheral T5CK =     { NONE, INPUT, &T5CKR } ;
const peripheral IC1 =      { NONE, INPUT, &IC1R } ;
const peripheral IC2 =      { NONE, INPUT, &IC2R } ;
const peripheral IC3 =      { NONE, INPUT, &IC3R } ;
const peripheral IC4 =      { NONE, INPUT, &IC4R } ;
const peripheral IC5 =      { NONE, INPUT, &IC5R } ;
const peripheral OC1 =      { 5, OUTPUT, NULL } ;
const peripheral OC2 =      { 5, OUTPUT, NULL } ;
const peripheral OC3 =      { 5, OUTPUT, NULL } ;
const peripheral OC4 =      { 5, OUTPUT, NULL } ;
const peripheral OC5 =      { 6, OUTPUT, NULL } ;
const peripheral REFCLKI =  { NONE, INPUT, &REFCLKIR } ;
const peripheral REFCLKO =  { 7, OUTPUT, NULL } ;
const peripheral U1CTS =    { NONE, INPUT, &U1CTSR } ;
const peripheral U1RTS =    { 1, OUTPUT, NULL } ;
const peripheral U1RX =     { NONE, INPUT, &U1RXR } ;
const peripheral U1TX =     { 1, OUTPUT, NULL } ;
const peripheral U2CTS =    { NONE, INPUT, &U2CTSR } ;
const peripheral U2RTS =    { 2, OUTPUT, NULL } ;
const peripheral U2RX =     { NONE, INPUT, &U2RXR } ;
const peripheral U2TX =     { 2, OUTPUT, NULL } ;
const peripheral SDI1 =     { NONE, INPUT, &SDI1R } ;
const peripheral SDO1 =     { 3, OUTPUT, NULL } ;
const peripheral SS1 =      { NONE, INPUT, &SS1R } ;
const peripheral SDI2 =     { NONE, INPUT, &SDI2R } ;
const peripheral SDO2 =     { 4, OUTPUT, NULL } ;
const peripheral SS2 =      { NONE, INPUT, &SS2R } ;
const peripheral OCFA =     { NONE, INPUT, &OCFAR } ;
const peripheral OCFB =     { NONE, INPUT, &OCFBR } ;
const peripheral C1OUT =    { 7, OUTPUT, NULL } ;
const peripheral C2OUT =    { 7, OUTPUT, NULL } ;
const peripheral C3OUT =    { 7, OUTPUT, NULL } ;

const pps_block GROUP1 = { &INT4, &T2CK, &IC4, &SS1, &REFCLKI, &U1TX, &U2RTS,  &OC1, &C2OUT, NULL } ;
const pps_block GROUP2 = { &INT3, &T3CK, &IC3, &U1CTS, &U2RX, &SDI1, &SDO1, &SDO2, &OC2, &C3OUT, NULL} ;
const pps_block GROUP3 = { &INT2, &T4CK, &IC1, &IC5, &U1RX, &U2CTS, &SDI2, &OCFB, &SDO1, &SDO2, &OC4, &OC5, &REFCLKO, NULL } ;
const pps_block GROUP4 = { &INT1, &T5CK, &IC2, &SS2, &OCFA, &U1RTS, &U2TX, &OC3, &C1OUT, NULL } ;

const io_port RA = { &TRISA, &LATA, &PORTA, &ODCA, &CNENA, &CNSTATA, &CNPUA, &CNPDA, &CNCONA, &PORTASET, &PORTACLR, &PORTAINV } ;
const io_port RB = { &TRISB, &LATB, &PORTB, &ODCB, &CNENB, &CNSTATB, &CNPUB, &CNPDB, &CNCONB, &PORTBSET, &PORTBCLR, &PORTBINV };

const pin RA0  = { &RA, 1,     &RPA0R,  &GROUP1, 0 } ;
const pin RA1  = { &RA, 2,     &RPA1R,  &GROUP2, 0 } ;
const pin RA2  = { &RA, 4,     &RPA2R,  &GROUP3, 0 } ;
const pin RA3  = { &RA, 8,     &RPA3R,  &GROUP4, 0 } ;
const pin RA4  = { &RA, 16,    &RPA4R,  &GROUP3, 2 } ;

const pin RB0  = { &RB, 1,     &RPB0R,  &GROUP4, 2 } ;
const pin RB1  = { &RB, 2,     &RPB1R,  &GROUP2, 2 } ;
const pin RB2  = { &RB, 4,     &RPB2R,  &GROUP3, 4 } ;
const pin RB3  = { &RB, 8,     &RPB3R,  &GROUP1, 1 } ;
const pin RB4  = { &RB, 16,    &RPB4R,  &GROUP1, 2 } ;
const pin RB5  = { &RB, 32,    &RPB5R,  &GROUP2, 1 } ;
const pin RB6  = { &RB, 64,    &RPB6R,  &GROUP3, 1 } ;
const pin RB7  = { &RB, 128,   &RPB7R,  &GROUP1, 4 } ;
const pin RB8  = { &RB, 256,   &RPB8R,  &GROUP2, 4 } ;
const pin RB9  = { &RB, 512,   &RPB9R,  &GROUP4, 4 } ;
const pin RB10 = { &RB, 1024,  &RPB10R, &GROUP4, 3 } ;
const pin RB11 = { &RB, 2048,  &RPB11R, &GROUP2, 3 } ;
const pin RB12 = { &RB, 4096,  &RPB12R, NULL,    0 } ;
const pin RB13 = { &RB, 8192,  &RPB13R, &GROUP3, 3 } ;
const pin RB14 = { &RB, 16384, &RPB14R, &GROUP4, 1 } ;
const pin RB15 = { &RB, 32768, &RPB15R, &GROUP1, 3 } ;

const pin_group open_drain_tolerant = { &RB5, &RB6, &RB7, &RB8, &RB9, &RB10, &RB11, NULL };
const pin_group analog_channels = { &RA0, &RA1, &RB0, &RB1, &RB2, &RB3, NULL, NULL, NULL, &RB15, &RB13, &RB12 } ;

inline void pin_set_direction(const pin *p, unsigned char direction){
    if(direction == INPUT) *(p->io->tris) |= p->mask;
    else *(p->io->tris) &= ~(p->mask);
}

inline void pin_set_output_state(const pin *p, unsigned char value){
    if(value == OUTPUT) *(p->io->lat) |= p->mask;
    else *(p->io->lat) &= ~(p->mask);
}

inline void pin_set_output_high(const pin *p){
    *(p->io->set) |= p->mask;
}

inline void pin_set_output_low(const pin *p){
    *(p->io->clr) |= p->mask;
}

inline void pin_invert(const pin *p){
    *(p->io->inv) |= p->mask;
}

inline unsigned char pin_read(const pin *p){
    return (*(p->io->port) & p->mask) == p->mask;
}

/*
 * Function only used by library. Sequential check of the PPS block given to
 * check if the pin belongs. I'd love to make a smarter search system, but
 * I don't trust (and I don't even think it's allowed) recursion on the PICs
 */
signed char check_for_pin_legality(const pps_block p, const peripheral *pr){
    unsigned char i;
    for(i = 0; p[i] != (const peripheral*)NULL; i++)
        if(p[i] == pr) return i;
    return -1;
}

unsigned char pin_assign_peripheral(const pin *p, const peripheral *peripheral){
    if(p->pps == NULL) return 0; /* Means the pin is not remappable (RB12) */
    if(check_for_pin_legality(*(p->pps), peripheral) == -1) return 0;
    if(peripheral->io == INPUT) *(peripheral->input_pps) = p->pps_input_code;
    else *(p->output_pps) = peripheral->output_pps_code;
    return 1;
}

signed char pin_is_in_group(const pin *p, const pin_group *pg){
    unsigned char i;
    for(i = 0; *(pg)[i] != NULL; i++)
        if(*(pg)[i] == p) return i;
    return -1;
}

inline unsigned char pin_open_drain_selection(const pin *p, unsigned char request){
    if(pin_is_in_group(p, &open_drain_tolerant) == -1) return 0;
    if(request == ON) *(p->io->odc) |= p->mask;
    else *(p->io->odc) &= ~(p->mask);
    return 1;
}

signed char pin_is_analog(const pin *p){
    unsigned char i;
    for(i = 0; i < 13; i++)
        if(p == analog_channels[i]) return i;
    return -1;
}

inline unsigned char pin_select_working_mode(const pin *p, unsigned char analog_digital){
    unsigned char ch = pin_is_analog(p);
    if(ch == -1) return 0;
    if(analog_digital == ANALOGIC) AD1CSSL |= (1 << ch);
    else AD1CSSL &= ~(1 << ch);
    return 1;   
}

inline void pin_assign_interrupt_on_change(const pin *p, unsigned char activated){
    if(activated == ON) *(p->io->cnen) |= p->mask;
    else *(p->io->cnen) &= ~(p->mask);
}

inline void pin_assign_pull_up(const pin *p, unsigned char activated){
    if(activated == ON) *(p->io->cnpu) |= p->mask;
    else *(p->io->cnpu) &= ~(p->mask);
}

inline void pin_assign_pull_down(const pin *p, unsigned char activated){
    if(activated == ON) *(p->io->cnpd) |= p->mask;
    else *(p->io->cnpd) &= ~(p->mask);
}

inline void port_set_direction(const io_port *p, unsigned int mask){
    *(p->tris) = mask;
}

inline void port_set_output_state(const io_port *p, unsigned int mask){
    *(p->lat) = mask;
}

inline void port_invert(const io_port *p, unsigned char mask){
    *(p->inv) = mask;
}

void port_set_change_notice_behaviour(const io_port *p, unsigned char active, unsigned char idle_state){
    /* Register bit for activation is 15 */
    if(active == ON) *(p->cnstat) |= (1 << 15);
    else *(p->cnstat) &= ~(1 << 15);
    if(idle_state == ON) *(p->cnstat) &= ~(1 << 13);
    else *(p->cnstat) |= (1 << 13);
}