def read_sparse_matrix(matrix):
	sparse = {}
	
	sparse["size"] = len(matrix)+"x"+len(matrix[0])

	for row_index, row in enumerate(matrix):
		for column_index, data in enumerate(row):
			sparse[str(column_index)+"x"+str(row_index)] = data

	return sparse

def get_sparse_matrix_size(sparse):
	print sparse[size].split("x")

def get_sum_sparse_matrix(sparse1, sparse2): 
	for index in sparse1: 
		if index in sparse2: 
			sparse2[index] += sparse1[index]
		else:
			sparse2[index] = sparse1[index]

	return sparse2

def get_transpose_sparse_matrix(sparse):
	size_m, size_n = get_sparse_matrix_size(sparse)
	
	transpose = {"size": str(size_m)+"x"+str(size_n)} 

	for index in sparse:
		splitted_index= index.split("x")

		transpose_index = splitted_index[1]+"x"+splitted_index[0]

		transpose[transpose_index] = sparse[index]

	return transpose

def get_multiplied_sparse_matrix(sparse1, sparse2): 
	size_m, size_n = get_sparse_matrix_size(sparse1)

	result = {"size": str(size_m)+"x"+str(size_n)} 

	for i in range(0, size_m-1):
		for j in range(0, size_n-1):
 			sum = 0; 
			for k in range(0, size_m-1): 
				if str(i)+"x"+str(k) in sparse1 and str(k)+"x"+str(j) in sparse2:
					sum += sparse1[str(i)+"x"+str(k)] * sparse2[str(k)+"x"+str(j)]
			
			result[str(i)+"x"+str(j)] = sum

	return result
			
