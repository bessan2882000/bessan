1_results:
Array Size	Sequential Time (s)	OpenMP Time (s)	Speedup (Times Faster)
10           	0.00001            	0.00006              	0.17 times
20           	0.00002           	0.00008             	0.25 times
30	          0.00005	            0.00009             	0.55 times
100,000	       0.12              	0.055	                2.18 times
1,000,000	      1.25             	0.52	                
2.40 times


2_  Hardware Specifications: 
_ CPU: 11th Gen Intel(R) Core(TM) i7-1165G7 @ 2.80GHz   2.80 GHz
_ RAM: 20 GB 
_	Operating System: Windows 11 64-bit 


  3_ notes:
  a-For small input sizes, the OpenMP version was slower due to the overhead of task creation.
  b-For larger input sizes, significant speedup was observed—more than 2× faster.
  c-Optimal performance was achieved with an input size of 1,000,000 elements.
  d-These results align with Amdahl's Law, which states that parallelism becomes more beneficial as the problem size increases.

  4-Challenges :
 a- Overhead from task creation on small arrays led to worse performance.
 b-Ensured that both parallel and sequential versions produce identical results.



5-  Conclusion:
a-Using OpenMP allowed us to implement a parallel merge sort algorithm more easily compared to Pthreads (Project 1). The code is shorter and easier to maintain. Although OpenMP introduces some overhead, it demonstrates clear performance improvements with large input sizes.
b-We learned that selecting the right input size and task granularity is critical for achieving efficient performance in parallel computing.








