package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"reflect"
)

// isTruthy replicates Python's if value checks
func isTruthy(v interface{}) bool {
	if v == nil {
		return false
	}

	rv := reflect.ValueOf(v)
	switch rv.Kind() {
	case reflect.Bool:
		return rv.Bool()
	case reflect.String:
		return rv.String() != ""
	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32, reflect.Int64:
		return rv.Int() != 0
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32, reflect.Uint64:
		return rv.Uint() != 0
	case reflect.Float32, reflect.Float64:
		return rv.Float() != 0
	case reflect.Slice, reflect.Array:
		return rv.Len() != 0
	case reflect.Map:
		return rv.Len() != 0
	default:
		// For structs etc., treat as true if not nil
		return true
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "Usage: filledness <jsonl_file>")
		os.Exit(1)
	}

	jsonlFile := os.Args[1]
	file, err := os.Open(jsonlFile)
	if err != nil {
		log.Fatalf("Failed to open file: %v", err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	maxCapacity := 1000 * 1024 * 1024
	scanner.Buffer(make([]byte, maxCapacity), maxCapacity)

	fieldCounts := make(map[string]int)
	totalLines := 0

	for scanner.Scan() {
		line := scanner.Text()
		totalLines++

		var data map[string]interface{}
		if err := json.Unmarshal([]byte(line), &data); err != nil {
			// If the line isn’t valid JSON, skip it
			log.Printf("Warning: skipping invalid JSON on line %d: %v", totalLines, err)
			continue
		}

		// Count truthy fields
		for field, value := range data {
			if isTruthy(value) {
				fieldCounts[field]++
			}
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatalf("Error reading file: %v", err)
	}

	// Print fill rates
	for field, count := range fieldCounts {
		percentage := float64(count) / float64(totalLines) * 100
		fmt.Printf("%s: %.2f%%\n", field, percentage)
	}
}
