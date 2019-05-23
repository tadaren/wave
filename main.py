import matplotlib.pyplot as plt

def main():
    with open('test3.wav', 'rb') as f:
        riff = f.read(4)
        file_size = f.read(4)
        wave = f.read(4)
        fmt = f.read(4)
        chunk_byte = f.read(4)
        fmt_id = f.read(2)
        channel = f.read(2)
        fs = f.read(2)
        fs_int = int.from_bytes(fs, 'little')
        data_speed = f.read(4)
        block_size = f.read(4)
        bit = f.read(2)
        data_id = f.read(4)
        size = f.read(4)

        byte = int.from_bytes(bit, 'little')//8
        size_int = int.from_bytes(size, 'little')//byte
        data = [int.from_bytes(f.read(byte), 'little', signed=True) for _ in range(size_int)]

    data2 = [e//2 for e in data]

    with open('out1.wav', 'wb') as f:
        f.write(riff)
        f.write(file_size)
        f.write(wave)
        f.write(fmt)
        f.write(chunk_byte)
        f.write(fmt_id)
        f.write(channel)
        f.write(fs)
        f.write(data_speed)
        f.write(block_size)
        f.write(bit)
        f.write(data_id)
        f.write(size)

        [f.write(d.to_bytes(byte ,'little', signed=True)) for d in data2]

    print(fs_int)
    fc = int(input())
    M = int(0.443 * fs_int / fc)
    # M = M + (0 if M%2 else 1)
    print(M)
    M = M + (M%2+1)%2
    M2 = M // 2

    pre = [data[0]]*M2
    suf = [data[-1]]*M2
    data3 = pre + data + suf

    print(len(data))
    print(len(data3))

    out_data = [0]*size_int
    for i in range(size_int):
        # print(sum(data3[i:i+M]))
        # if i < 10:
        #     print(f"{i} {i+M} {sum(data3[i:i+M])} {sum(data3[i:i+M])//M} {data[i]}")
        out_data[i] = sum(data3[i:i+M])//M

    with open('out2.wav', 'wb') as f:
        f.write(riff)
        f.write(file_size)
        f.write(wave)
        f.write(fmt)
        f.write(chunk_byte)
        f.write(fmt_id)
        f.write(channel)
        f.write(fs)
        f.write(data_speed)
        f.write(block_size)
        f.write(bit)
        f.write(data_id)
        f.write(size)

        [f.write(d.to_bytes(byte ,'little', signed=True)) for d in out_data]

    plt.plot(data, lw=0.5)
    plt.plot(out_data, lw=0.5)
    # # plt.xlim(-10, size_int+10)
    plt.show()


if __name__ == "__main__":
    main()