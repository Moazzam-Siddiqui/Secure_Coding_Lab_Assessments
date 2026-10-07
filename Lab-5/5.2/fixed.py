from pathlib import Path

SAFE_DIR = Path("safe_files").resolve()

filename = input("Enter filename: ")

requested_path = (SAFE_DIR / filename).resolve()

# Allow access only when the resolved path stays inside SAFE_DIR
try:
    requested_path.relative_to(SAFE_DIR)
except ValueError:
    print("Access denied: file is outside the safe directory.")
else:
    if not requested_path.is_file():
        print("File not found.")
    else:
        with requested_path.open("r", encoding="utf-8") as file:
            content = file.read()
        print(content)