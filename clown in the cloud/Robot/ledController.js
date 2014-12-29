var util = require('util');

module.exports = function() {
    
    var mraa = require("mraa"); //require mraa
    var i2C = new mraa.I2c(0);
    var ledAddresses = [0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40];
    
    function init() {
        console.log("Initializing LED matrix controller");
        i2C.address(0x70);
        writeBuffer(new Buffer([0x21]));
        writeBuffer(new Buffer([0xEF]));
        writeBuffer(new Buffer([0x81]));
    }
    
    function clear() {
        console.log("LED: clear");
        writeBuffer(new Buffer([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ]));
    }
    
    function writeBuffer(buffer)
    {
        i2C.write(buffer.toString('ascii'));
    }
    
    function writeBitmap(pattern) 
    {
        var start = new Buffer([0x00]);
        var ledPatterns = [start];
        pattern.forEach(function(row) {
            var bytePattern = 0x00;
            var bitIndex = 0;
            row.forEach(function(bit) {
                if(bit === 1) {
                    bytePattern += ledAddresses[bitIndex];
                }
                bitIndex++;
            });
            ledPatterns.push(new Buffer([ bytePattern, 0x00 ]));
        });

        var buf = Buffer.concat(ledPatterns);
        writeBuffer(buf);
    };
    
    function smile() {
        console.log("LED: smile");
        
        var smiley = new Buffer([0x00, 0x1E, 0x00, 0x21, 0x00, 0xD2, 0x00, 0xC0, 0x00, 0xD2, 0x00, 0xCC, 0x00, 0x21, 0x00, 0x1E, 0x00]);
        
        writeBuffer(smiley);
    }
    
    init();
    
  return {
      clear: clear,
      smile: smile
  };
}();