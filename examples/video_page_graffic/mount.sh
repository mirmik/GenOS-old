sudo losetup -f ~/multiboot/hard_disk.img
sudo kpartx -v -a /dev/loop0
sudo mount /dev/mapper/loop0p1 /mnt
