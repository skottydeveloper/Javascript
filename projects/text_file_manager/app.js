let fileHandle;

async function openFile() {
    [fileHandle] = await window.showOpenFilePicker({
        types: [{ description: "Text Files (.txt)", accept: { 'file/*': ['.txt'] }}],
        excludeAcceptAllOption: true,
        multiple: true,
    });

    if (!fileHandle) {
        return;
    }

    const fileData = await fileHandle.getFile();
    const text = await fileData.text();
    textArea.innerText = text;

    if (textArea.innerText == "") {
        textArea.innerText = "{}";
    }
}

async function saveFile() {
    const stream = await fileHandle.createWritable();
    await stream.write(textArea.innerText);
    await stream.close();
}

async function createFile() {
    [fileHandle] = await window.showSaveFilePicker({
        suggestedName: 'new-text.json',
        types: [{ description: "Text Files (.txt)", accept: { 'file/*': ['.txt'] }}],
        excludeAcceptAllOption: true,
        multiple: false,
    });

    if (!fileHandle) {
        return;
    }
}