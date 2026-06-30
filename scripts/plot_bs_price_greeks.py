import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/bs_price_greeks_vs_spot.csv")

plt.figure()
for T in sorted(df["maturity"].unique()):
    sub = df[df["maturity"] == T]
    plt.plot(sub["spot"], sub["price"], label=f"T = {T}")

payoff = df[df["maturity"] == df["maturity"].min()]
plt.plot(payoff["spot"], payoff["payoff"], label="Payoff", linestyle="--")

plt.axvline(100, linestyle="--", label="Strike")
plt.xlabel("Spot")
plt.ylabel("Call price")
plt.title("European Call Price vs Spot")
plt.legend()
plt.grid(True)
plt.savefig("plots/call_price_vs_spot.png", dpi=300)
plt.show()


plt.figure()
for T in sorted(df["maturity"].unique()):
    sub = df[df["maturity"] == T]
    plt.plot(sub["spot"], sub["delta"], label=f"T = {T}")

plt.axvline(100, linestyle="--", label="Strike")
plt.xlabel("Spot")
plt.ylabel("Delta")
plt.title("European Call Delta vs Spot")
plt.legend()
plt.grid(True)
plt.savefig("plots/call_delta_vs_spot.png", dpi=300)
plt.show()


plt.figure()
for T in sorted(df["maturity"].unique()):
    sub = df[df["maturity"] == T]
    plt.plot(sub["spot"], sub["gamma"], label=f"T = {T}")

plt.axvline(100, linestyle="--", label="Strike")
plt.xlabel("Spot")
plt.ylabel("Gamma")
plt.title("European Call Gamma vs Spot")
plt.legend()
plt.grid(True)
plt.savefig("plots/call_gamma_vs_spot.png", dpi=300)
plt.show()