$ErrorActionPreference = 'Stop'

$compiler = Get-Command gcc -ErrorAction SilentlyContinue
if ($null -eq $compiler) {
    throw 'gcc was not found. Install a GCC toolchain that supports AddressSanitizer.'
}

$sourceDirectory = Join-Path $PSScriptRoot 'fixed'
$buildDirectory = Join-Path $PSScriptRoot 'build'
New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null

Get-ChildItem -Path $sourceDirectory -Filter '*.c' | ForEach-Object {
    $executable = Join-Path $buildDirectory ($_.BaseName + '.exe')
    & gcc -std=c11 -Wall -Wextra -Werror -fsanitize=address -g $_.FullName '-o' $executable
    if ($LASTEXITCODE -ne 0) {
        throw "ASan compilation failed for $($_.Name)."
    }

    Write-Host "Running $($_.Name)..."
    & $executable
    if ($LASTEXITCODE -ne 0) {
        throw "ASan run failed for $($_.Name)."
    }
}

Write-Host 'All fixed snippets completed cleanly with AddressSanitizer.'
