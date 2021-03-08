# Solving the dynamic k-center problem.

The dynamic k-center problem asks for k center points which minimize the maximum distance 
to the current set of points in a given metric space under the insertion and deletion of points.

## Installation Notes.

### Downloading:
```
git clone https://github.com/alexandersvozil/DynamicKCenterClustering/
```

### Compiling:

## Running Instructions.
To run the k-center algorithm on a given instance use the following command.
`<path_to_points>` - path to the file which contains all points of the metric space.
`<path_to_updates>` - path to the file which contains the updates 
`k` - number of centers we want to maintain
`epsilon` - the algorithm guarantees a (2+epsilon) solution.
`nr_of_points` - The algorithm considers the first `nr_of_points` lines of `<path_to_points>` file.
```
./kcenter <path_to_points> <path_to_updates> k epsilon nr_of_points 
```
Example: `./kcenter "../../../experiments/datasets/random/random_2M" "../../../experiments/queries/200000_sliding" 20 4 200000`


