# Red Black Tree
(Summary and Review on “A Concurrent Red-Black Tree” by Juan Besa and Yadran Eterovic)
<br>
By Anirudh Sharma and Bhavil Ahuja

## Abstract—

Multiple Data Structures exist currently, for the utility of software engineers in the creation of data indexing services or be it, databases. The utility of data structures is vast, and even the types of data structures we study are highly stratified. 
Concurrency in Programming is a hot topic with increasing number of applications, and is being employed in almost all fields. The ultimate objective currently, is to search for methods to simplify the use of Concurrent Programming, and one such solution provided to us is “Concurrent Data Structures”. 
Concurrent Data Structures are easy to use, and are very effective in solving issues related to concurrency.
“However, there has been varied success in parallelizing data structures. For some – e.g., linked lists and queues – there are natural ways to achieve parallelism. But dictionaries (or ordered maps) are harder to parallelize. In a sequential environment they are typically implemented as balanced binary search trees of logarithmic depth such as AVL trees and red–black trees; but the concurrent versions of these trees were not considered efficient solutions until recently.” 

### I.	INTRODUCTION
Red Black Trees are more or less modified versions of AVL Trees, in short, Red-Black Trees ~ AVL Trees (Adelson-Velsky and Landis Trees), except Red-Black Trees have an upper hand over AVL Trees as they have a better relaxed balance condition. Red-Black trees usually require O(1) rotations to correct an imbalance, to that of O(log N) in case of an AVL Tree, ‘N’ being the number of nodes in the tree. Hence, Red-Black Trees have the potential to perform better than AVL Trees in High Contention scenarios. We propose to you that Concurrent Red-Black Trees can improve the performance of Concurrent Dictionaries.

### II.	METHODS
<b>i.	Understanding the Problem:</b><br><br>
A Red-Black Tree is a self-balancing Binary Search Tree. <br>
It maintains its balance by using rebalancing operations that rotate and/or recolor nodes to always fulfill the following five red–black rules: 
1.	Every node has a color, red or black. Depending on their color they are called red nodes or black nodes. 
2.	The root node is a black node. 
3.	Every simple path from the root to a leaf has the same number of black nodes; this number is called the black depth of the tree. 
4.	No red node has a red child. 
5.	Every null node is a black node.

The red–black rules guarantee O(log N) time complexity for get’s, insertion’s and removal’s, where N is the number of nodes in the tree. Insertions and removals are update operations, and the thread performing the update is an updater. An imbalance is any node, or parent–child pair of nodes, that breaks a red–black rule; when the tree has an imbalance we say it is imbalanced. To correct an imbalance an updater uses rebalancing operations – rotations and recoloring – to reestablish the rules.

Red-Black Trees are used extensively as “dictionaries”, and with multithreaded applications have become more widespread, concurrent dictionaries are becoming a more important part of programs. However, Red-Black Trees and BST’s, in general, have never had a relevant role in “Concurrent Dictionaries” due to the complexities involved in their usage. Instead, ‘skip lists’ are used, for “Concurrent Dictionaries”. 
By the correction of Concurrent Red-Black Trees, we think they can also become practical concurrent dictionaries.

<b>ii. Approach to addressing and solving the problem.</b><br><br>
  <b>A.	Past Work(s) Referred</b><br>
      The researchers studied on the work done previously by different people in the same field:<br>
-	<b>Chromatic tree proposed by Nurmi and Soisalon-Soininen -</b> Here, the rules of the red-black tree are weakened to increase the update speed, drawback being that they do not guarantee logarithmic depth.
-	<b>log n rebalancing operations by  Boyar and Larsen -</b> they guarantee a maximum time complexity of O(log n) for rebalancing, drawback being that the lock a large number of nearby nodes.
-	<b>Relaxed balanced red-black trees by Hanke et al. and Larsen -</b> similar to chromatic trees but differ in a way that their updating thread does not remove nodes, it only marks them for removal. The actual removal is done by their rebalancing threads.
-	<b>Concurrent AVL trees by Bronson et al. -</b> they used a technique called hand-over-hand optimistic validation, where there is no need to lock the nodes while traversing the tree.

  <b>B.	Analysis and Ulterior solutions from these work(s)</b><br>
      The researchers in their contribution –<br>
- Used both hand-over-hand optimistic validation and partially external trees and applied them to a concurrent red–black tree.
-	Defined new rebalancing operations and concept of double black nodes in which double black nodes can hold a maximum of 2 black nodes for better efficiency. 
-	Used a partially extended red black tree. 
-	Did not use relaxed rebalancing, instead the updating thread corrects the fault, if any. 
-	Do not guarantee log n updates and searches due to scheduling issues. log n is guaranteed only when there are no updates being upload or the current thread does not interfere with any other thread.

iii.	Algorithm proposed by the researchers/Implementation:
 
<b>Updates -</b> The updater thread must solve the imbalance caused while changing the value by applying rebalancing operations. Even if it is fixed by some other updater, it is considered to be solved.
 
<b>Insertions -</b> Same as in Binary Search tree, inserted node is red and if it's parent is found to be red, it causes a red red imbalance.
 
<b>Removals - </b><br>
Step 1: set node's value = NULL<br>
Step 2: Ideally, the route node should be swapped with it's successor but this may be very costly in concurrent tree hence this isn't supported and the removal is concluded. If the route node has a single child, then the child is linked to route node's parent thus unlinking the route node. In case the route node is black, firstly the imbalances are resolved and then only linking-unlinking is done.

<b>Steps of rebalancing -</b>
1. Determine whether imbalance is present
2. Access n's grandparent first and the n's parent.
3. To determine the operation to use, assess the vicinity of the node.
4. Apply the relevant operation as the updater already holds required locks.
5. Release all the locks gained from step 2 and 3(if any).
6. Check for further imbalance caused and resolve it.<br>
<b>NOTE:</b> The researchers have preferred single rotations over double as double rotations are costlier due to their requirement of one extra node to be locked. They mentioned only those cases where imbalanced node is the left child of its parent. The case of right child has a symmetrical version.

<b>Resolving red-red imbalances:</b><br>
This balance is generated when the inserted node's parent is also red.<br>
In this case, the parent red node holds the imbalance.

Abbreviations used:<br>
n: the node that owns the imbalance<br>
p: n’s parent<br>
s: n’s sibling; the other child of p<br>
g: n’s grandparent; the parent of p<br>
c: n’s red child in a red–red imbalance.<br>

<i>Case 1:</i> both n and s are red.<br>
In case a new red-red-imbalance is generated, the same thing is repeated for grandparent g.<br>
Since the operation is symmetric, any imbalance on s is solved and any other thread working on the same concludes the process.<br>

<i>Case 2:</i> n is red and s is black and the outer child of n is red.<br>

<i>Case 3:</i> n is red and s is black and the inner child of n is red.<br><br>

<b>Resolving double black imbalances:</b><br>
<i>Case 4:</i> n is double black and s is black with black children.<br>

<i>Case 5:</i> n is double black and s is red.<br>

<i>Case 6:</i> n is double black and s is black with a red child.<br><br>

<b>Resolving root issues:</b><br>
It has two cases - root is red or root is double black, so to resolve both of this, just change the root color to black.

### III.	RESULTS AND CONCLUSION
The concurrent red-black tree proposed by the author is effective in many scenarios.<br>
This tree is 5% better than Bronson's AVL tree and 72% better than best-known concurrent skip list solution. Also, it performs 13% less rotations than AVL trees.<br>
Addition of least possible number of rebalancing operations allows us to solve different cases efficiently. All the operations used affect very small neighbourhood, thereby improving concurrency of several updates. However, due to scheduling issues, O(log n) time complexity cannot be guaranteed.

#### REFERENCES
[1] Nurmi, E. Soisalon-Soininen, Chromatic binary search trees, Acta Informatica 33 (5) (1996) 547–557.<br>
[2] R. Sedgewick, Left-leaning red–black tree. 2008, September. From <i>www.cs.princeton.edu/rs/talks/LLRB/LLRB.pdf</i> <br>
[3] N. Shavit, Data structures in the multicore age, Communications of the ACM (2011) 76–84.<br>
[4] S. Hanke, The performance of concurrent red–black tree algorithms, in: Algorithm Engineering, Springer, Berlin, Heidelberg, 1999, pp. 286–300. [5] S. Hanke, T. Ottmann, E. Soisalin-Soininen, Relaxed balanced red–black trees, Lecture Notes in Computer Science 1203 (1997) 193–204.<br>
[6] L.J. Guibas, R. Sedgewick, A dichromatic framework for balanced trees, in: Proceedings of the 19th IEEE Symp. Foundations of Computer Science, Ann Arbor, MI, USA, 1978, pp. 8–21<br>
[7] J. Boyar, K.S. Larsen, Efficient rebalancing of chromatic search trees, Journal of Computer and System Sciences 49 (3) (1994) 667–682.<br>
[8] N.G. Bronson, J. Casper, H. Chafi, K. Olukotun, A practical concurrent binary search tree, SIGPLAN Notices 45 (5) (2010) 257–268.<br>
[9] M. Herlihy, Y. Lev, V. Luchangco, N. Shavit, A provably correct scalable concurrent skip list, in: Proceedings of the Twenty-Second Annual Symposium on Principles of Distributed Computing, PODC’03, ACM, New York, NY, USA, 2003, pp. 92–101.<br>
