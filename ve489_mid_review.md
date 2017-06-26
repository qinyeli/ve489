# VE489 Mid Review -- Data Link Layer

Author: Qinye Li
Date: June 27, 2017

{:TOC}

---

# Mid Schedule

**Time**: next class
**Location**: this classroom
**Cheatsheet**: A4, double-sided


* Qinye's office hour migrated to Wednesday @ ylm center
* Send me an email beforehand if you have a rather complicated question.


---

# Background

## Link Layer
* Logic Link Control (LLC) Layer
	* Error Control
	* Flow Control (vs. Congestion Control)
* Medium Access Control (MAC) Layer
	* Framing, checksum
	* Link Control

* Understand that different services can be provided

---

# Highlights

* Framing
	* Bit oriented framing & bit-stuffing
* ARQ
	* Stop and Wait
	* Go Back N
	* Selective Repeat

---

# Framing

## Why framing?

Sender needs to set boundaries in between continuous bits so that these bits can be sent out **frame by frame**;
Receiver relies on the boundaries to **detect start and end of a new frame**.

---

## How framing?

* **Character-oriented framing** (Flog bytes with byte stuffing)
* **Bit-oriented framing** (Flag bits with **bit stuffing**)

---

## Character-oriented framing
* **Binary Synchronous Communication**
	* Start flag: STX
    * End flag: ETX
    * Escape: DLE
* **Point-to-Point Protocol** (**PPP**)
    * Flag: 0x7E (01111110)
    * Escape: 0x7D (01111101)
    * For 0x7E or 0x7D in the original data, add excape and XOR with 0x20 (00100000)
    * TODO: e.g.
---

## Bit-oriented framing
* Indicate start and end of frames with 0111110 (0x7E)
* Stuff a 0 after 11111 in the original data

* TODO: homework as sample


---

# ARQ (Automatic Repeat Request)

## Why ARQ?

To ensure a sequence of information packets are delivered in-order, error-free and without loss or duplication despite tranmission errors and loess.

In a word: **To ensure in-order, error-free delivery**

---

## How ARQ?

* Stop and Wait
* Go-Back N
* Selective Repeat

---

## Components of ARQ

* Timeout
* ACK & NACK
* Sequence Number
* Sending Window
* Receiving Window

TODO: relatiosn between seqno and sliding window

---

## Sliding Window

Left edge of window

- sender: beginnign of unacked data
- receiver: beginning of expected / undelivered data

Right edge: left edge + const

---

TODO: add exmaples to these ARQ

## Stop-and Wait ARQ

* Transmit and wait for ACK
* Does not work well for high BDP (hish speed or long prog delay)

---

## Go-Back N ARQ

* Receiver uses cumulative ack and discards out-of sequence packets

* Retransmit **from** the next expected packet


* For m bit sequence number, Ws <= 2^m

---

## Selective Repeat ARQ

* Receiver uses selective ack and buffers out-of-sequence packets

* Retransmit only unack'd packets


* For m bit sequence number, Ws + Wr <= 2^m
