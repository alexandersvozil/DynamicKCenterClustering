# Solving the dynamic k-center problem.

The dynamic k-center problem asks for k center points which minimize the maximum distance 
to the current set of points in a given metric space under the insertion and deletion of points.
The following paper is the basis for the code:
#### Fully Dynamic k-Center Clustering in Low Dimensional Metrics - Gramoz Goranci, Monika Henzinger, Dariusz Leniowski, Christian Schulz and Alexander Svozil
Link: `https://epubs.siam.org/doi/abs/10.1137/1.9781611976472.11`

## Installation Notes.
The algorithm uses the Eigen3 3.3 library : `https://eigen.tuxfamily.org/index.php?title=Main_Page`


### Downloading:
```
git clone https://github.com/alexandersvozil/DynamicKCenterClustering/
```

### Compiling:
```
cd CoverTree/src
mkdir build
cd build
cmake ..
make
```

## Running Instructions.
To run the k-center algorithm on a given instance use the following command.
- `<path_to_points>` - path to the file which contains all points of the metric space.
- `<path_to_updates>` - path to the file which contains the updates 
- `k` - number of centers we want to maintain
- `epsilon` - the algorithm guarantees a (2+epsilon) solution.
- `nr_of_points` - The algorithm considers the first `nr_of_points` lines of `<path_to_points>` file.
```
./kcenter <path_to_points> <path_to_updates> k epsilon nr_of_points 
```
Example: `./kcenter "../../../experiments/datasets/random/random_2M" "../../../experiments/queries/200000_sliding" 20 4 200000`


The algorithm supports only 2 dimensional euclidean metrics right now and works with the `double`
data type.

### Points File
This file is part of the input. 
#### Syntax:
```
point-id <tab>	x-coordinate y-coordinate
```

#### Example for points file. (first parameter):
```
0	0.2051748826 -0.03279284533
1	0.2042274195 -0.03338254464
2	0.2045793658 -0.03323874977
3	0.204321128 -0.03308959114
4	0.2044415052 -0.03132793941
5	0.2041610155 -0.03284095243
6	0.2027101161 -0.03148450163
7	0.2053811775 -0.03223630335
8	0.2033150797 -0.03341741213
9	0.2041826239 -0.03379518549
```

### Update File
#### Syntax:
- `ix` insert point with id `x` (assumes that point x exists in the points file)
- `dx` delete point with id `x` (assumes that point x is already inserted)
- `q` query current k-center solution (assumes that at least one point is already inserted), the
  output consists of the ids (corresponding to the linenumbers in the points file) which are in the
  current k-center solution.

#### Example for updates file (second parameter):
```
i152904
i199689
i156276
i79935
d152904
i20423
i6179
d156276
i138189
i92976
i16895
q
```

### Full Example
The Makefile compiles a full example of the program called 'test_cover' using subsets of the
original datasets used in the paper.

Here is a link to the full datasets (and also reduced datasets) as used in the paper:
https://mega.nz/folder/IYRi0b5B#fd1-6dsrwAYNtchSysgD9w


# Licence
The program is licenced under MIT licence. If you publish results using our algorithms, please acknowledge our work by quoting the following paper:

```
@inproceedings{DBLP:conf/alenex/GoranciHLSS21,
  author    = {Gramoz Goranci and
               Monika Henzinger and
               Dariusz Leniowski and
               Christian Schulz and
               Alexander Svozil},
  title     = {Fully Dynamic \emph{k}-Center Clustering in Low Dimensional Metrics},
  booktitle = {Proceedings of the Symposium on Algorithm Engineering and Experiments,
               {ALENEX} 2021, Virtual Conference, January 10-11, 2021},
  pages     = {143--153},
  publisher = {{SIAM}},
  year      = {2021},
  url       = {https://doi.org/10.1137/1.9781611976472.11},
  doi       = {10.1137/1.9781611976472.11},
}

```
