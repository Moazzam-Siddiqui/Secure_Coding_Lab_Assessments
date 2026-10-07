# insecure_app.py

import random
import subprocess

# Insecure: hard-coded password
ADMIN_PASSWORD = "SuperSecret123!"


def generate_token():
    # Insecure: random is not cryptographically secure
    return str(random.randint(100000, 999999))


def run_command(user_input):
    # Insecure: shell=True with user-controlled input
    return subprocess.run(
        f"echo {user_input}",
        shell=True,
        capture_output=True,
        text=True,
    )


if __name__ == "__main__":
    print("Token:", generate_token())
    print(run_command("hello").stdout)