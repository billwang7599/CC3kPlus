#!/bin/bash

# Find all .h files in the current directory and subdirectories
find . -type f -name "*.h" | while read -r file; do
  # Extract filename without path and extension, and convert to uppercase
  filename=$(basename "$file")
  guard=$(echo "${filename}" | tr '[:lower:]' '[:upper:]' | sed 's/\./_/g')

  # Check if the file already has include guards
  if ! grep -q "#ifndef ${guard}" "$file"; then
    echo "Adding include guards to $file"

    # Create a temporary file
    tmpfile=$(mktemp)

    # Write include guards to the temporary file
    echo "#ifndef ${guard}" > "$tmpfile"
    echo "#define ${guard}" >> "$tmpfile"
    echo "" >> "$tmpfile"
    cat "$file" >> "$tmpfile"
    echo "" >> "$tmpfile"
    echo "#endif // ${guard}" >> "$tmpfile"

    # Move the temporary file back to the original file
    mv "$tmpfile" "$file"
  else
    echo "Include guards already present in $file"
  fi
done
