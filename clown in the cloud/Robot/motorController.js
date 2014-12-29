/* Motor controller
  
  Uses DFRobot Motor Shield with default jumper configuration
  http://www.dfrobot.com/index.php?route=product/product&product_id=69
*/    
    

module.exports = function() {
    
    var mraa = require("mraa"); //require mraa
    
    // Motor A
    //Initialize Digital Pin #4 (D4)
    var aDir = new mraa.Gpio(4);
    aDir.dir(mraa.DIR_OUT);
    //Initialize PWM on Digital Pin #5 (D5)
    var aSpeed = new mraa.Pwm(5, -1, false);
    aSpeed.enable(false);
    aSpeed.period_us(2000);

    // Motor B
    //Initialize Digital Pin #7 (D7)
    var bDir = new mraa.Gpio(7);
    bDir.dir(mraa.DIR_OUT);
    //Initialize PWM on Digital Pin #6 (D6)
    var bSpeed = new mraa.Pwm(6, -1, false);
    bSpeed.enable(false);
    bSpeed.period_us(2000);

    
    function go() {
        console.log("Action: GO");
        aDir.write(0);      // forward
        aSpeed.enable(true);
        aSpeed.write(1);    // 100% on
        bDir.write(0);      // forward
        bSpeed.enable(true);
        bSpeed.write(1);    // 100% on
    };
        
    function stop() {
        console.log("Action: STOP");
        aSpeed.enable(false);
        aSpeed.write(0);    // 0% on
        bSpeed.enable(false);
        bSpeed.write(0);    // 0% on
    };
  
    function left() {
        console.log("Action: LEFT");
        aDir.write(0);      // forward
        aSpeed.enable(true);
        aSpeed.write(0.5);  // 50% on
        
        bDir.write(1);      // back
        bSpeed.enable(true);// 
        bSpeed.write(0.5);    // 50% on
    };
  
    function right() {
        console.log("Action: RIGHT");
        aDir.write(1);      // back
        aSpeed.enable(true);
        aSpeed.write(0.5);    // 50% on
        
        bDir.write(0);      // forward
        bSpeed.enable(true);
        bSpeed.write(0.5);    // 50% on

    };
    
    function doAction(actionName)
    {
        if (actionName == 'go')
        {
            go();
        }
        else if (actionName == 'stop')
        {
            stop();
        }
        else if (actionName == 'left')
        {
            left();
        }
        else if (actionName == 'right')
        {
            right();
        }
    }
    
    function demo() {
        console.log("Motor demo");
        var idx = 0;
        var actions = [
            go, 
            stop,
            left, 
            right];

        setInterval(function () {
            actions[idx]();
            idx = (idx + 1) % 4;
        }, 3000);
    }
    
    
  return {
      go: go,
      stop: stop,
      left: left,
      right: right,
      demo: demo,
      doAction: doAction
  };
}();