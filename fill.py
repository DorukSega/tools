import json
import argparse

def calculate_filledness(jsonl_file):
    field_counts = {}
    total_lines = 0

    with open(jsonl_file, 'r', encoding='utf-8') as file:
        for line in file:
            total_lines += 1
            data = json.loads(line.strip())

            for field, value in data.items():
                if field not in field_counts:
                    field_counts[field] = 0
                
                if value:
                    field_counts[field] += 1

    if total_lines == 0:
        print("No data found in the file.")
        return

    filledness_percentages = {field: (count / total_lines) * 100 for field, count in field_counts.items()}

    for field, percentage in filledness_percentages.items():
        print(f'{field}: {percentage:.2f}%')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Calculate the percentage of non-empty fields in a JSONL file.")
    parser.add_argument("jsonl_file", help="Path to the JSONL file")
    args = parser.parse_args()

    calculate_filledness(args.jsonl_file)
