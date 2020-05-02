import datetime
import glob
import json

def read_library(filename):
    with open(filename, 'r') as f:
        lib = f.read().splitlines()
    title = ''
    body = []
    state = 0
    for line in lib:
        if line.startswith('#pragma region '):
            state = 1
            title = line[15:]
        elif state == 1 and line.startswith('#pragma endregion'):
            state = 2
            break
        elif state == 1:
            body.append(line)

    if state != 2:
        return None
    else:
        return {
            'prefix': title,
            'description': '競プロ用ライブラリ - ' + title,
            'body': body
        }

def generate():
    snippet = {}
    for fn in glob.glob('./**/*.hpp', recursive=True):
        elem = read_library(fn)
        if elem is not None:
            snippet[elem['prefix']] = elem
    with open('cpp.json', 'w') as f:
        f.write('// last modified: ' + str(datetime.datetime.now()) + '\n')
        json.dump(snippet, f, ensure_ascii=False, indent=4)

if __name__ == '__main__':
    generate()
