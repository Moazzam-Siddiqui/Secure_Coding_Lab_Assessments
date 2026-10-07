import secrets

def generate_token():
    # Cryptographically secure token generation
    return secrets.token_urlsafe(32)

def run_command(user_input):
    # No shell is required for this simple operation.
    return user_input

if __name__ == "__main__":
    print("Token:", generate_token())
    print(run_command("hello"))