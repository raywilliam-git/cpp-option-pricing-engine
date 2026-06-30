import pandas as pd
import matplotlib.pyplot as plt

# Asian vs European
df = pd.read_csv("results/asian_vs_european.csv")

plt.figure(figsize=(9, 5))
plt.plot(df["spot"], df["european_price"], label="European call")
plt.plot(df["spot"], df["asian_price"], label="Asian call")
plt.xlabel("Spot")
plt.ylabel("Option price")
plt.title("European vs Asian Call Price")
plt.legend()
plt.grid(True)
plt.savefig("plots/asian_vs_european.png", dpi=300, bbox_inches="tight")
plt.show()


# Asian monitoring dates
df = pd.read_csv("results/asian_monitoring_dates.csv")

plt.figure(figsize=(9, 5))
for d in sorted(df["time_steps"].unique()):
    sub = df[df["time_steps"] == d]
    plt.plot(sub["spot"], sub["asian_price"], label=f"d = {d}")

plt.xlabel("Spot")
plt.ylabel("Asian call price")
plt.title("Asian Call Price vs Number of Monitoring Dates")
plt.legend()
plt.grid(True)
plt.savefig("plots/asian_monitoring_dates.png", dpi=300, bbox_inches="tight")
plt.show()


# Confidence interval percentage
plt.figure(figsize=(9, 5))
for d in sorted(df["time_steps"].unique()):
    sub = df[df["time_steps"] == d]
    plt.plot(sub["spot"], sub["ci_width_percent"], label=f"d = {d}")

plt.xlabel("Spot")
plt.ylabel("CI width / price (%)")
plt.title("Relative Confidence Interval Width")
plt.legend()
plt.grid(True)
plt.savefig("plots/asian_ci_width_percent.png", dpi=300, bbox_inches="tight")
plt.show()