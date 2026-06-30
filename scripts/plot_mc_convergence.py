import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/mc_convergence.csv")

# Graphe 1 : convergence complète
plt.figure(figsize=(9, 5))
plt.plot(df["simulations"], df["mc_price"], label="Monte Carlo price")
plt.plot(df["simulations"], df["bs_price"], label="Black-Scholes price")
plt.fill_between(
    df["simulations"],
    df["ci_lower"],
    df["ci_upper"],
    alpha=0.2,
    label="95% confidence interval"
)
plt.xlabel("Number of simulations")
plt.ylabel("Call price")
plt.title("Monte Carlo convergence with 95% confidence interval")
plt.legend()
plt.grid(True)
plt.savefig("plots/mc_convergence_full.png", dpi=300, bbox_inches="tight")
plt.show()

# Graphe 2 : zoom propre
df_zoom = df[df["simulations"] >= 500]

plt.figure(figsize=(9, 5))
plt.plot(df_zoom["simulations"], df_zoom["mc_price"], label="Monte Carlo price")
plt.plot(df_zoom["simulations"], df_zoom["bs_price"], label="Black-Scholes price")
plt.fill_between(
    df_zoom["simulations"],
    df_zoom["ci_lower"],
    df_zoom["ci_upper"],
    alpha=0.2,
    label="95% confidence interval"
)
plt.xlabel("Number of simulations")
plt.ylabel("Call price")
plt.title("Monte Carlo convergence zoomed")
plt.legend()
plt.grid(True)
plt.ylim(9.5, 11.5)
plt.savefig("plots/mc_convergence_zoom.png", dpi=300, bbox_inches="tight")
plt.show()

# Graphe 3 : largeur de l'intervalle
plt.figure(figsize=(9, 5))
plt.plot(df["simulations"], df["ci_width"])
plt.xlabel("Number of simulations")
plt.ylabel("95% confidence interval width")
plt.title("Confidence interval width vs number of simulations")
plt.grid(True)
plt.xscale("log")
plt.yscale("log")
plt.savefig("plots/mc_confidence_width_loglog.png", dpi=300, bbox_inches="tight")
plt.show()