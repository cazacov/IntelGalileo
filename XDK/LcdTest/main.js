/*
JavaScript demo for Jhd1313m1 i2c controller for HD44780 based displays
with an RGB backlight such as the Grove RGB i2c LCD display.
*/

var lcdModule = require('jsupm_i2clcd');
var lcd = new lcdModule.Jhd1313m1(0, 0x3E, 0x62);

lcd.setColor(0,255,0); // 0% Red, 100% Green, 0% Blue

lcd.setCursor(0,0);
lcd.write("Hello World!");
lcd.setCursor(1,2);
lcd.write("Hallo Welt!");
lcd.close();

console.log("Done");

var phi = 0.0;
setInterval(function() {
    red   = Math.sin(phi + 0) * 127 + 128;
    green = Math.sin(phi + Math.PI*2/3) * 127 + 128;
    blue  = Math.sin(phi + Math.PI*4/3) * 127 + 128;
    lcd.setColor(red, green, blue);    
    phi = phi + 0.1;
}, 50);