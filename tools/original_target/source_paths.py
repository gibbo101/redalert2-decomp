"""Resolve catalog paths without inferring filenames from original addresses."""
from pathlib import Path


def source_path(repository, value):
    path = Path(value)
    if (path.is_absolute() or path.as_posix() != value or '..' in path.parts or
            len(path.parts) < 3 or path.parts[:2] != ('src', 'recovered') or
            path.suffix != '.cpp' or
            any(not all(c.isascii() and (c.isalnum() or c in '_.-') for c in part)
                for part in path.parts)):
        raise ValueError('Noncanonical source path outside canonical tree')
    repository = Path(repository).resolve()
    root = repository / 'src/recovered'
    resolved = (repository / path).resolve()
    if root.resolve() != root or not resolved.is_relative_to(root):
        raise ValueError('Source escapes tree')
    return resolved
