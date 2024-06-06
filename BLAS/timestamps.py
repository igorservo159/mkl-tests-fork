import subprocess

def BLAS_exec(args, timestamps):
    try:
        comando = ['make', 'run', f'ARGS={args}']
        resultado = subprocess.run(comando, check=True, text=True, capture_output=True)
        timestamps.append(resultado.stdout)
    except subprocess.CalledProcessError as e:
        print(e)
        print(e.stdout)
        print(e.stderr)

def run_experiments(matrix_type, initial_size, final_size, interval, filename_prefix):
    precision_types = ['s', 'd', 'c', 'z']
    timestamps = {pt: [] for pt in precision_types}

    for pt in precision_types:
        for num in range(initial_size, final_size, interval):
            arguments = f"{num} {num} {num} {num} mm {pt} {matrix_type} n 1"
            BLAS_exec(arguments, timestamps[pt])

        with open(f"./experiments/{filename_prefix}/{pt}_{filename_prefix}_matrix.txt", 'w') as file:
            for exp in timestamps[pt]:
                file.write(exp)

initial_size = 300
final_size = 600
interval = 100
matrix_type = 's'

# General matrices
if matrix_type == 'g':
    run_experiments('g', initial_size, final_size, interval, 'general')

# Sparse general matrices
elif matrix_type == 'ge':
    run_experiments('ge', initial_size, final_size, interval, 'sparse_general')

# Symmetric matrices
elif matrix_type == 's':
    run_experiments('s', initial_size, final_size, interval, 'symmetric')

# Sparse decompressed matrices
elif matrix_type == 'ed':
    run_experiments('ed', initial_size, final_size, interval, 'decompressed_sparse')

# Sparse compressed matrices
elif matrix_type == 'ec':
    run_experiments('ec', initial_size, final_size, interval, 'compressed_sparse')