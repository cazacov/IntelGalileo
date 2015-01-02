var mraa = require("mraa"); //require mraa
var i2C = new mraa.I2c(0);

i2C.address(0x70);
i2C.write(String.fromCharCode(0x21)); // Writes one byte: 0x21
i2C.write(0xEF); 

console.log("Done");

    
function init() {
    console.log("Initializing LED matrix controller");
    i2C.address(0x70);
    writeBuffer(new Buffer([0x21]));    // turn on oscillator
    
    var st = String.fromCharCode(0xF001); // Translated in UTF-8 as  EF,80,81
    i2C.write(st);

    //writeBuffer(new Buffer([0xEF]));    // Brightness 15                
    //writeBuffer(new Buffer([0xF001]));    // Turn off blinking
}
    
function clear() {
    console.log("LED: clear");
    writeBuffer(new Buffer([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]));
}
    
function writeBuffer(buffer)
{
        /*
        var arr = new Uint32Array(buffer);
        var b2 = new Buffer(arr.length * 2);
        
        var str = ""; 
        for(var i = 0; i < arr.length; i++) {
            b2[i*2] = arr[i];
            b2[i*2+1] = 0;
        }
        i2C.write(str);
        */
        //var strBuf = buffer.toString('ascii');
        //strBuf = b2.toString('utf16le');
    console.log("Writing bufer of " + buffer.length + " bytes");
    var str = buffer.toString('ascii');
    i2C.write(str);
}
    
    
    
function smile() {
    console.log("LED: smile");
    var smiley = new Buffer([0x00, 0x03, 0x00, 0x13, 0x00, 0x20, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x13, 0x00, 0x03, 0x00, 0x00, 0x00]);
    writeBuffer(smiley);
}
    
//init();

//clear();
//smile();    
