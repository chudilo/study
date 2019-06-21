#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/time.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("chudik");

static const unsigned long chudFS_MAGIC_NUMBER = 0x13131313;

static void chudFS_put_super(struct super_block *sb)
{
    printk(KERN_INFO "chudFS super block destroyed!\n");
}

static struct super_operations const chudFS_super_ops = {
    .put_super = chudFS_put_super,
    .statfs = simple_statfs ,
    .drop_inode = generic_delete_inode ,
};

static struct inode *chudFS_make_inode(struct super_block *sb, int mode)
{
    struct inode *ret = new_inode(sb);
    if (ret) {
        inode_init_owner(ret, NULL, mode);
        ret->i_size = PAGE_SIZE;
        ret->i_atime = ret->i_mtime = ret->i_ctime = current_time(ret);
    }
    return ret;
}

static int chudFS_fill_sb(struct super_block *sb, void *data, int silent)
{
    struct inode *root = NULL;

    sb->s_blocksize = PAGE_SIZE;
    sb->s_blocksize_bits = PAGE_SHIFT;
    sb->s_magic = chudFS_MAGIC_NUMBER;
    sb->s_op = &chudFS_super_ops;

    root = chudFS_make_inode(sb, S_IFDIR | 0755);
    if (!root)
    {
        printk(KERN_ERR "inode allocation failed!\n");
       return -ENOMEM;
    }

    root->i_op = &simple_dir_inode_operations;
    root->i_fop = &simple_dir_operations;

    sb->s_root = d_make_root(root);
    if (!sb->s_root)
    {
        printk(KERN_ERR "root creation failed!\n");
        return -ENOMEM;
    }

	return 0;
}

//^
static struct dentry *chudFS_mount(struct file_system_type *type,
                                int flags, char const *dev, void *data)
{
    struct dentry *const entry = mount_bdev(type, flags, dev, data, chudFS_fill_sb);
    if (IS_ERR(entry))
        printk(KERN_ERR "chudFS mounting failed!\n");
    else
        printk(KERN_INFO "chudFS mounted\n");
    return entry;
}
// ^
static struct file_system_type chudFS_type = {
    .owner = THIS_MODULE,
    .name = "chudFS",
    .mount = chudFS_mount,
    .kill_sb = kill_block_super,
};

static int __init chudFS_init(void)
{
    int ret = register_filesystem(&chudFS_type);
    if (ret != 0) {
        printk(KERN_ERR "Cannot register filesystem!\n");
        return ret;
    }

    printk(KERN_INFO "chudFS module loaded\n");
    return 0;
}

static void __exit chudFS_exit(void)
{
    int ret = unregister_filesystem(&chudFS_type);

    if (ret != 0)
        printk(KERN_ERR "Cannot unregister filesystem!\n");
    printk(KERN_INFO "chudFS module unloaded\n");
}

module_init(chudFS_init);
module_exit(chudFS_exit);
