# Tenda Router AC Series Vulnerability

This vulnerability lies in the `/goform/setWAN` page which influences the lastest version of Tenda Router AC11. ([AC11_V02.03.01.104_CN](https://www.tenda.com.cn/download/detail-3163.html))

## Vulnerability description

![3](../10/3.png)

There is a stack buffer overflow vulnerability in the `wanBasicCfg` module.


![1](1.png)

the program reads user input `wanMask` into variable `v10` and uses `nvram_set` function to set the nvram variable `wan0_netmask`, without porper length check. 

![2](2.png)

the prograrm will then use `nvram_get` function to put that input into variable `v54` and copy to a fixed destination, which will cause a stack overflow.

So by POSTing the page `/goform/setWAN` with proper `wanMask`, the attacker can easily perform a **Deny of Service Attack** or **Remote Code Execution** with carefully crafted overflow data.

## POC

![poc](poc.png)

## Timeline

- 2022.01.09 report to CVE & CNVD

## Acknowledgment

Credit to [@cpegg](https://github.com/cpeggg), [@leonW7](https://github.com/leonW7) and [@peanuts](https://github.com/peanuts62) from Shanghai Jiao Tong University and TIANGONG Team of Legendsec at Qi'anxin Group.
