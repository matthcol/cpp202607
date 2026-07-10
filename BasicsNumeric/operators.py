import numpy as np

print("before creating")
_ = input()
m = np.random.normal(10.0, 2.5, 125_000_000) # 1Go

print("vector created")
_ = input()

m *= 2 # in place : still 1 Go

print("vector *2 in-place")
_ = input()

r = m
m = m * 2 # +1Go provisoire

print("vector *2 duplicated")
_ = input()