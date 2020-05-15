mkdir -p genereated
for inputFile in ./*.txt; do
	name=$(basename "$inputFile" .txt)
	newName="$PWD/genereated/$name.txt"
	echo "$newName"
	$1 < "$inputFile" > "$newName"
done