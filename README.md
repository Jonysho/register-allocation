1. Assume an ordered list of colours (eg, red, black, blue, etc, here denoted by A, B, C, …)
2. Assume an interference graph, where nodes are numbered: 1, 2, 3, …
3. Rank nodes (that is, live ranges) of the interference graph according to the number of
neighbours in descending order. In case of a tie (that is, nodes with the same number of
neighbours) the node with the lowest id takes priority.
4. Follow the ranking to assign colours from the list of colours. For each node, select the first
colour from the list that is not used by the node’s neighbours.
5. Keep following the ranking and repeating step 4 until all nodes are coloured.