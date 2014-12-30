module.exports = function() {
    
    var mraa = require("mraa"); //require mraa
    var i2C = new mraa.I2c(0);
    
    function init() {
        console.log("Initializing LED matrix controller");
        i2C.address(0x70);
        writeBuffer(new Buffer([0x21]));    // turn on oscillator
        writeBuffer(new Buffer([0x81]));    // Turn off blinking
        writeBuffer(new Buffer([0xEF]));    // Brightness 15        
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
        */
        //i2C.write(str);
        //var strBuf = buffer.toString('ascii');
        //strBuf = b2.toString('utf16le');
        
        i2C.write(buffer.toString('ascii'));
    }
    
    
    
    function smile() {
        console.log("LED: smile");
        var smiley = new Buffer([0x00, 0x03, 0x00, 0x13, 0x00, 0x20, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x13, 0x00, 0x03, 0x00, 0x00, 0x00]);
        writeBuffer(smiley);
    }
    
    init();
    
  return {
      clear: clear,
      smile: smile
  };
}();