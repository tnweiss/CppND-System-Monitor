#include <iostream>
#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization(Processor &prev) {
    // help from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

    // if the previous is null return 0
    if (&prev == nullptr){
        return 0.0;
    }

    long prevIdle = prev.Idle() + prev.Iowait();
    long idle = this->idle + this->iowait;

    long prevNonIdle = prev.User() + prev.Nice() + prev.System() + prev.Irq() + prev.SoftIrq() + prev.Steal();
    long nonIdle = this->user + this->nice + this->system + this->irq + this->softirq + this->steal;

    long prevTotal = prevNonIdle + prevIdle;
    long total = idle + nonIdle;

    float totald = total - prevTotal;
    float idled = idle - prevIdle;

    return (totald - idled) / totald;
}