import pandas as pd

# Load the CSV file into a DataFrame
df = pd.read_csv('wyniki.csv')

# Filter rows with specific 'wariant' values
filtered_df = df[df['wariant'].isin(['KONC-SITO-1', 'KONC-SITO-2'])]

# Initialize a dictionary to store the minimum 'avgczas' for each ('min', 'max') pair
min_avgczas = {}

# Iterate over the filtered DataFrame and find the minimum 'avgczas' for each ('min', 'max') pair
for _, row in filtered_df.iterrows():
    key = (row['min'], row['max'])
    if key not in min_avgczas or row['avgczas'] < min_avgczas[key]:
        min_avgczas[key] = row['avgczas']

# Update the 'przyspieszenie' column based on the calculated minimum 'avgczas'
df['przyspieszenie'] = df.apply(lambda row: min_avgczas[(row['min'], row['max'])] / row['avgczas'], axis=1)

df['efektywnosc'] = df.apply(lambda row: row['przyspieszenie'] / row['watki'], axis=1)

def format_scientific(value):
    if value > 100000 or value < 0.0001:
        return '{:.3e}'.format(value)
    elif isinstance(value, float):
        return '{:.4f}'.format(value)
    else:
        return '{:d}'.format(value)

print(min_avgczas)

# Save the modified DataFrame back to the CSV file
df.to_csv('wyniki.csv', index=False, float_format=format_scientific)