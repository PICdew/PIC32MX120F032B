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

const pin RA0  = { &RA, 1,     &RPA0R,  &GROUP1 } ;
const pin RA1  = { &RA, 2,     &RPA1R,  &GROUP2 } ;
const pin RA2  = { &RA, 4,     &RPA2R,  &GROUP3 } ;
const pin RA3  = { &RA, 8,     &RPA3R,  &GROUP4 } ;
const pin RA4  = { &RA, 16,    &RPA4R,  &GROUP3 } ;

const pin RB0  = { &RB, 1,     &RPB0R,  &GROUP4 } ;
const pin RB1  = { &RB, 2,     &RPB1R,  &GROUP2 } ;
const pin RB2  = { &RB, 4,     &RPB2R,  &GROUP3 } ;
const pin RB3  = { &RB, 8,     &RPB3R,  &GROUP1 } ;
const pin RB4  = { &RB, 16,    &RPB4R,  &GROUP1 } ;
const pin RB5  = { &RB, 32,    &RPB5R,  &GROUP2 } ;
const pin RB6  = { &RB, 64,    &RPB6R,  &GROUP3 } ;
const pin RB7  = { &RB, 128,   &RPB7R,  &GROUP1 } ;
const pin RB8  = { &RB, 256,   &RPB8R,  &GROUP2 } ;
const pin RB9  = { &RB, 512,   &RPB9R,  &GROUP4 } ;
const pin RB10 = { &RB, 1024,  &RPB10R, &GROUP4 } ;
const pin RB11 = { &RB, 2048,  &RPB11R, &GROUP2 } ;
const pin RB12 = { &RB, 4096,  &RPB12R, NULL    } ;
const pin RB13 = { &RB, 8192,  &RPB13R, &GROUP3 } ;
const pin RB14 = { &RB, 16384, &RPB14R, &GROUP4 } ;
const pin RB15 = { &RB, 32768, &RPB15R, &GROUP1 } ;

const pin_group open_drain_tolerant = { &RB5, &RB6, &RB7, &RB8, &RB9, &RB10, &RB11, NULL };
const pin_group analog_channels = { &RA0, &RA1, &RB0, &RB1, &RB2, &RB3, &RB15, &RB13, &RB12, NULL } ;