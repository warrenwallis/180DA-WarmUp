# A Shallow Deep Dive Into the CAN Protocol

What if I told you that there exists a simple low-cost technology that you can utilize in your projects to land that much coveted summer internship?

Join me on this journey of discovering what this protocol is about and, to give a little incentive, I guide you on a simple application where we create a reflex game between two people using this technology.

You CAN do this!

## What is CAN

Controller Area Network or CAN is a network technology primarily used in embedded systems that provide fast communication amongst microcontrollers while being cost-effective. Notably, a network can function as a series of nodes and operate without a host computer [[1](https://github.com/warrenwallis/180DA-WarmUp/blob/main/misc/wiki-article-first-draft.md#sealing-this-can-post)]. 

*Ok, but what does that mean!?* It means that there isn't a central computer delegating tasks and controlling how messages are sent or received. Like some cryptocurrencies, a CAN bus is a decentralized network that is able to send messages efficiently across its network.

Some characteristics of CAN:
- ~~preserving foods~~
- needs only two wires to communicate
- operates at data rates up to 1 Mb/s
- supports a max of 8 Bytes per message frame
- supports message priority
- supports ID lengths of of 11-bits and 29-bits

Some industries of where CAN is used:
- automotive (where it began)
- medical instruments
- manufacturing
- elevators and escalators (where I use it for my job :nail_care:)

Similar technologies to CAN:
- ~~electric can-opener~~
- ethernet w/ TCP/IP (expensive :thumbsdown:)
- FPD-link

## Digging Deeper into :canned_food:

### Hardware Principles

As mentioned earlier, a network using CAN only needs two wires to operate:

*insert image here*

This significantly reduces the wires needed to connect the network, and is why it was and still is popular in the automobile industry. The motivation behind the CAN protocol was to reduce costs by reducing the use of copper wire:

*insert image here*

We can break down a node into three parts:
1. Microprocessor
    Hello
2. CAN controller
3. Transceiver


### Software Principles

## Sealing this CAN Post

## Links

1. [Wikipedia](https://en.m.wikipedia.org/wiki/CAN_bus)
2. [CopperHillTech](https://copperhilltech.com/a-brief-introduction-to-controller-area-network/)
3. [TexasInstruments-1](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf?ts=1675960976305&ref_url=https%253A%252F%252Fwww.google.com%252F)
4. [TexasInstruments-2](https://www.ti.com/lit/an/slyt560/slyt560.pdf?ts=1676009390287&ref_url=https%253A%252F%252Fwww.google.com%252F#:~:text=Still%2C%20Ethernet%20can%20transport%20data,provid%2D%20ing%20much%20more%20bandwidth)
5. [Adafruit](https://learn.adafruit.com/adafruit-feather-m4-can-express)
