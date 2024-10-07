#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import sys
import numpy as np


df_1 = pd.read_csv(sys.argv[1])
df_1 = df_1.loc[:, ~df_1.columns.str.contains("^Unnamed")]
arr_1 = df_1.to_numpy()[0]

df_2 = pd.read_csv(sys.argv[2])
df_2 = df_2.loc[:, ~df_2.columns.str.contains("^Unnamed")]
arr_2 = df_2.to_numpy()[0]

fig = plt.figure(figsize=(10, 8), dpi=100)
axes = fig.add_axes((0, 0, 1, 1))

Ts = [i for i in range(128, 4224, 128)]

axes.set_title("Matrix (N x N, float) multiplication comparison")
axes.set_xlabel("Matrix dimension, N")
axes.set_ylabel("Time, ms")

axes.plot(
    np.array(Ts),
    arr_1,
    marker="o",
    markersize=5,
    markeredgecolor="k",
    markeredgewidth=1,
    label="Naive",
)
axes.plot(
    np.array(Ts),
    arr_2,
    marker="o",
    markersize=5,
    markeredgecolor="k",
    markeredgewidth=1,
    label="Fast",
)

axes.grid(True, color="0.6", dashes=(5, 2, 1, 2))


fig.savefig("comparison.pdf", bbox_inches="tight")
fig.savefig("comparison.png", bbox_inches="tight")
