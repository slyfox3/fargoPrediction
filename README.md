# fargoPrediction

This project computes the likelyhood of match results, given players' FargoRate ratings.

Example usage:

* `Player1` has rating `610` and races to `9`
* `Player2` has rating `545` and races to `6`

It predicts the most possible outcome of the match is 9:5
```
$ ./a.out 610 545 9 6
 9: 0	 1.18% ( 1.19% simulated)
 9: 1	 4.14% ( 4.19% simulated)
 9: 2	 8.06% ( 8.10% simulated)
 9: 3	11.51% (11.53% simulated)
 9: 4	13.44% (13.59% simulated)
 9: 5	13.60% (13.48% simulated)
 8: 6	 8.67% ( 8.69% simulated)
 7: 6	 8.73% ( 8.64% simulated)
 6: 6	 8.34% ( 8.28% simulated)
 5: 6	 7.45% ( 7.38% simulated)
 4: 6	 6.10% ( 6.16% simulated)
 3: 6	 4.44% ( 4.40% simulated)
 2: 6	 2.72% ( 2.74% simulated)
 1: 6	 1.27% ( 1.31% simulated)
 0: 6	 0.35% ( 0.32% simulated)

P(Player 1 wins) = 51.93%
```

 
Fargo Rate official site:
https://www.fargorate.com/
