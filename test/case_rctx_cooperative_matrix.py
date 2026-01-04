#!/usr/bin/env python3

import numpy as np
import torch
import torch.nn.functional as F


class Conv2DParams:
    IH = 1080
    IW = 1920
    IC = 3
    OH = 540
    OW = 960
    OC = 16
    KH = 3
    KW = 3
    stride = 2
    padding = 1
    dilation = 1


def gen(params: Conv2DParams):
    # yout = np.zeros((1, params.OH, params.OW, params.OC), dtype=np.float32)
    xinp = np.zeros((1, params.IH, params.IW, params.IC), dtype=np.float32)
    kern = np.zeros((params.KH, params.KW, params.IC, params.OC), dtype=np.float32)
    bias = np.zeros((params.OC,), dtype=np.float32)
    buf = np.zeros_like(xinp).flatten()
    for k in range(buf.size):
        buf[k] = float(k % 255) / 255.0
    # yout.flat[:] = buf[: yout.size]
    xinp.flat[:] = buf[: xinp.size]
    kern.flat[:] = buf[: kern.size]
    bias.flat[:] = buf[: bias.size]
    xinp = torch.tensor(xinp, dtype=torch.float32)
    kern = torch.tensor(kern, dtype=torch.float32)
    bias = torch.tensor(bias, dtype=torch.float32)
    return (xinp, kern, bias)


def conv2d(USE_NHWC):
    params = Conv2DParams()
    xinp, kern, bias = gen(params)

    if USE_NHWC:
        xinp = xinp.permute(0, 3, 1, 2)
        kern = kern.permute(3, 2, 0, 1)
    else:
        xinp = xinp.reshape(1, params.IC, params.IH, params.IW)
        kern = kern.reshape(params.OC, params.IC, params.KH, params.KW)
    yout = F.conv2d(xinp, kern, bias, params.stride, params.padding, params.dilation)
    yout = F.relu(yout)
    if USE_NHWC:
        yout = yout.permute(0, 2, 3, 1)

    yout = yout.numpy().flatten()
    yout = yout[:: yout.size // 11]
    print(", ".join([f"{y:9.6f}" for y in yout]))


conv2d(True)
conv2d(False)
