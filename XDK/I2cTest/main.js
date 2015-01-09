/*
Simple library for controlling Adafruit LED 1.2" 8x8 Matrix
https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix

Wiring: 
GND -> Galileo GND
VCC -> Galileo 5V
SDA -> Galileo analog pin 4
SCL -> Galileo analog pin 5
*/

var mraa = require("mraa"); //require mraa
var i2C = new mraa.I2c(0);

// helper function to go from hex val to dec
function char(x) { return parseInt(x, 16); }

// Must be called once before using other functions
function init() {
    console.log("Initializing LED matrix controller");
    i2C.address(0x70);
    i2C.writeByte(char('0x21'));    // Turn on oscillator
    i2C.writeByte(char('0xef'));    // Brightness 15
    i2C.writeByte(char('0x81'));    // No blinking
}

/* Writes the Buffer of 8 bytes in the display's memory
    Attention: matrix columns are mapped to the bits as following:
    7 0 1 2 3 4 5 6
*/
function writeBuffer(buffer)
{
    // Add write command (zero byte) at the head of buffer
    var rawBuffer = new Buffer(buffer.length * 2 + 1);
    
    rawBuffer[0] = 0x00; // Write command
    
    for (var i = 0; i < buffer.length; i++)
    {
        rawBuffer[i*2 + 1] = buffer[i];
        rawBuffer[i*2 + 2] = 0;
    }
    i2C.write(rawBuffer);
}

// Clears the matrix
function clear() {
    console.log("LED: clear");
    var allZeroes = 
    writeBuffer(new Buffer([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]));
    
}
    
// Shows a smiling face
function smile() {
    console.log("LED: smile");
    var smiley = new Buffer([0x1E, 0x21, 0xCA, 0xD0, 0xD0, 0xCA, 0x21, 0x1E]);
    writeBuffer(smiley);
}
    

init();

clear();
smile();    
