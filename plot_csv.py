#!/usr/bin/env python
#-*- coding: utf-8 -*-
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv


def extract_csv(filename, save=False):
    # Extracting
    f = open(filename,'r')
    content = f.read().split("\n")
    sizes = [int(x.split(" ")[0]) for x in content[:-2]]
    rows = [int(x.split(" ")[-1]) for x in content[:-2]]
    return (sizes,rows)
    
if __name__ == "__main__":
    aos = extract_csv("nbody-struct-aos.csv");
    soa = extract_csv("nbody-struct-soa.csv");
    
    plt.figure(1)
    plt.subplot(111)
    save_aos = aos[1][0]
    save_soa = soa[1][0]
    for i in range(len(aos[0])):
        aos[1][i] = save_aos/float(aos[1][i])
        soa[1][i] = save_soa/float(soa[1][i])
    aos = plt.plot(aos[0], aos[1], 'b', label='aos-avx512')
    soa = plt.plot(soa[0], soa[1], 'g', label='soa-avx512')
    plt.legend(loc=1, bbox_to_anchor=(1,0.87))

    plt.xlabel('nombre de processus')
    plt.ylabel('Speed up')    
    plt.title('Speedup openmp nbody')    
    plt.show()
        
