

# Specify the output zip file name
output_zip="cc3k.zip"


# Zip all files in the directory
zip -r "$output_zip" . -x "*.git*" -x "*.DS_Store" -x "*.zip" -x "*.sh" -x "*.md" -x "*.pdf" -x "*.png" -x "*.jpg" -x "*.jpeg" -x "*.gif" -x "*.bmp" -x "*.tiff" -x "*.tif" -x "*.ico" -x ".vscode/*"

echo "Files zipped successfully!"