#!/bin/bash

# Получаем абсолютный путь к папке скриптов
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Переходим в корень проекта Hydra
cd "$SCRIPT_DIR/.."

echo "=== Building Hydra Engine (Debug) ==="
if ! make config=debug; then
    echo "Build failed! Exiting..."
    exit 1
fi

echo "=== Starting Hydra Editor ==="

# Заходим в рабочую директорию редактора для корректных путей к ассетам
pushd HydraEditor > /dev/null

# Запускаем редактор
./../bin/Debug-linux-x86_64/HydraEditor/HydraEditor

popd > /dev/null

echo "=== Hydra Editor exited ==="
