#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization(Processor&);  // TODO: See src/processor.cpp
  Processor(long userP, long niceP, long systemP, long idleP,
    long iowaitP, long irqP, long softirqP, long stealP, long guestP,
    long guestNiceP): user(userP), nice(niceP), system(systemP), idle(idleP),
    iowait(iowaitP), irq(irqP), softirq(softirqP), steal(stealP), guest(guestP),
    guestNice(guestNiceP){};
  Processor(): user(0), nice(0), system(0), idle(0), iowait(0), irq(0), softirq(0), steal(0), guest(0), guestNice(0){};

  long User(){return this->user;}
  long Nice(){return this->nice;}
  long System(){return this->system;}
  long Idle(){return this->idle;}
  long Iowait(){return this->iowait;}
  long Irq(){return this->irq;}
  long SoftIrq(){return this->softirq;}
  long Steal(){return this->steal;}
  long Guest(){return this->guest;}
  long GuestNice(){return this->guestNice;}

  // TODO: Declare any necessary private members
 private:
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
    long guest;
    long guestNice;
};

#endif