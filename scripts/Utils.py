import sys
import os
import platform
import requests
import time
import urllib.error

from zipfile import ZipFile


def GetSystemEnvironmentVariable(name):
    """Get system environment variable (cross-platform)."""
    if platform.system() == "Windows":
        try:
            import winreg
            key = winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE,
                                   r"System\CurrentControlSet\Control\Session Manager\Environment")
            return winreg.QueryValueEx(key, name)[0]
        except Exception:
            return None
    else:
        return os.environ.get(name)


def GetUserEnvironmentVariable(name):
    """Get user environment variable (cross-platform)."""
    if platform.system() == "Windows":
        try:
            import winreg
            key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, r"Environment")
            return winreg.QueryValueEx(key, name)[0]
        except Exception:
            return None
    else:
        return os.environ.get(name)


def DownloadFile(url, filepath):
    filepath = os.path.abspath(filepath)
    os.makedirs(os.path.dirname(filepath), exist_ok=True)

    if isinstance(url, list):
        for url_option in url:
            print("Downloading", url_option)
            try:
                DownloadFile(url_option, filepath)
                return
            except urllib.error.URLError as e:
                print(f"URL Error encountered: {e.reason}. Proceeding with backup...\n")
                if os.path.exists(filepath):
                    os.remove(filepath)
            except urllib.error.HTTPError as e:
                print(f"HTTP Error encountered: {e.code}. Proceeding with backup...\n")
                if os.path.exists(filepath):
                    os.remove(filepath)
            except Exception:
                print("Something went wrong. Proceeding with backup...\n")
                if os.path.exists(filepath):
                    os.remove(filepath)
        raise ValueError(f"Failed to download {filepath}")

    if not isinstance(url, str):
        raise TypeError("Argument 'url' must be of type list or string")

    with open(filepath, 'wb') as f:
        headers = {
            'User-Agent': (
                "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/83.0.4103.97 Safari/537.36"
            )
        }
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get('content-length')

        if total is None:
            f.write(response.content)
        else:
            downloaded = 0
            total = int(total)
            startTime = time.time()
            for data in response.iter_content(chunk_size=max(int(total / 1000), 1024 * 1024)):
                downloaded += len(data)
                f.write(data)
                done = int(50 * downloaded / total)
                percentage = (downloaded / total) * 100
                elapsedTime = time.time() - startTime
                avgKBPerSecond = (downloaded / 1024) / elapsedTime
                avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
                if avgKBPerSecond > 1024:
                    avgSpeedString = '{:.2f} MB/s'.format(avgKBPerSecond / 1024)
                sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format(
                    '█' * done, '.' * (50 - done), percentage, avgSpeedString))
                sys.stdout.flush()
    sys.stdout.write('\n')


def UnzipFile(filepath, deleteZipFile=True):
    zipFilePath = os.path.abspath(filepath)
    zipFileLocation = os.path.dirname(zipFilePath)

    zipFileContent = {}
    zipFileContentSize = 0

    with ZipFile(zipFilePath, 'r') as zipFileFolder:
        for name in zipFileFolder.namelist():
            zipFileContent[name] = zipFileFolder.getinfo(name).file_size
        zipFileContentSize = sum(zipFileContent.values())
        extractedContentSize = 0
        startTime = time.time()

        for zippedFileName, zippedFileSize in zipFileContent.items():
            UnzippedFilePath = os.path.abspath(f"{zipFileLocation}/{zippedFileName}")
            os.makedirs(os.path.dirname(UnzippedFilePath), exist_ok=True)
            if os.path.isfile(UnzippedFilePath):
                zipFileContentSize -= zippedFileSize
            else:
                zipFileFolder.extract(zippedFileName, path=zipFileLocation, pwd=None)
                extractedContentSize += zippedFileSize
            try:
                done = int(50 * extractedContentSize / zipFileContentSize)
                percentage = (extractedContentSize / zipFileContentSize) * 100
            except ZeroDivisionError:
                done = 50
                percentage = 100
            elapsedTime = time.time() - startTime
            try:
                avgKBPerSecond = (extractedContentSize / 1024) / elapsedTime
            except ZeroDivisionError:
                avgKBPerSecond = 0.0
            avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
            if avgKBPerSecond > 1024:
                avgSpeedString = '{:.2f} MB/s'.format(avgKBPerSecond / 1024)
            sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format(
                '█' * done, '.' * (50 - done), percentage, avgSpeedString))
            sys.stdout.flush()
    sys.stdout.write('\n')

    if deleteZipFile:
        os.remove(zipFilePath)