filename = input("Enter filename: ")

# Insecure: user-controlled path is opened directly
with open(filename, "r") as file:
    content = file.read()

print(content)
