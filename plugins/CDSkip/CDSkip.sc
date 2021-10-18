CDSkip : MultiOutUGen {
    *ar { |in, maxDelay = 2.0, autoMode = 0, autoSpeed = 1, skipTrigger = 0, resetTrigger = 0, pos = 0, freeze = 0, clean = 0|
        if(skipTrigger.rate != \audio) {
            skipTrigger = T2A.ar(skipTrigger);
        };
        if(resetTrigger.rate != \audio) {
            resetTrigger = T2A.ar(resetTrigger);
        };
        if(pos.rate != \audio) {
            pos = K2A.ar(pos);
        };
        ^this.multiNew('audio', in[0], in[1], maxDelay, autoMode, autoSpeed, skipTrigger, resetTrigger, pos, freeze, clean);
    }

    init { |... theInputs|
        inputs = theInputs;
        ^this.initOutputs(2, rate);
    }

    checkInputs {
        ^this.checkValidInputs;
    }
}
