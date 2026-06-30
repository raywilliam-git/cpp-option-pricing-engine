import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/mc_repeated_estimates.csv")

# group by N and compute std
std_df = df.groupby("simulations")["mc_price"].std().reset_index()

plt.figure(figsize=(9,5))
plt.plot(std_df["simulations"], std_df["mc_price"])

plt.xscale("log")
plt.yscale("log")

plt.xlabel("Number of simulations (N)")
plt.ylabel("Standard deviation of MC estimates")
plt.title("Standard deviation of Monte Carlo price estimates")

plt.grid(True)
plt.savefig("plots/mc_std_vs_N.png", dpi=300, bbox_inches="tight")
plt.show()




# histogram for one fixed N

N_fixed = 1000

subset = df[df["simulations"] == N_fixed]

bs_price = subset["bs_price"].iloc[0]

plt.figure(figsize=(9,5))

plt.hist(subset["mc_price"], bins=40, density=True, alpha=0.75)

plt.axvline(
    bs_price,
    linestyle="--",
    label="Black-Scholes price"
)

plt.xlabel("Call price estimate")
plt.ylabel("Density")

plt.title(f"Distribution of Monte Carlo estimates (N={N_fixed})")

plt.legend()
plt.grid(True)

plt.savefig("plots/mc_histogram.png", dpi=300, bbox_inches="tight")
plt.show()