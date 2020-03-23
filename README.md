# Conpad

## What's this?
A little utility I use to combine text files with a header including the original filename.
I wrote this because I had some configuration files that I needed to combine into a single one but still wanted to keep track of what the original files did.

## Example
fileA

```
Hello
```

fileB
```
Goodbye
```

conpad output
```
### fileA
Hello

### fileB
Goodbye
```
