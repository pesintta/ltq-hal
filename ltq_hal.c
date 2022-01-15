#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

#include <linux/proc_fs.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "ltq_hal.h"

struct dentry* g_ltq_hal_debugfs_dir;

static int ltq_hal_debugfs_cfg1_show(struct seq_file *s, void *unused)
{
	int i;

#define CFG1_PRINT(field) seq_printf(s, "\t" #field ": %d\n", GEN_MODE_CFG->field)

	seq_printf(s, "gen_mode_cfg1:\n");

	CFG1_PRINT(app2_indirect);
	CFG1_PRINT(us_indirect);
	CFG1_PRINT(us_early_discard_en);
	CFG1_PRINT(classification_num);
	CFG1_PRINT(ipv6_rout_num);
	// res1:2
	CFG1_PRINT(session_ctl_en);
	CFG1_PRINT(wan_hash_alg);
	CFG1_PRINT(brg_class_en);
	CFG1_PRINT(ipv4_mc_acc_mode);
	CFG1_PRINT(ipv6_acc_en);
	CFG1_PRINT(wan_acc_en);
	CFG1_PRINT(lan_acc_en);
	// res2:3
	CFG1_PRINT(sw_iso_mode);
	CFG1_PRINT(sys_cfg);

	seq_printf(s, "\n");


#define CFG2_PRINT(field) seq_printf(s, "\t" #field ": %d\n", GEN_MODE_CFG2->field)

	seq_printf(s, "gen_mode_cfg2:\n");

	// res1:24
	CFG2_PRINT(itf_outer_vlan_vld);

	seq_printf(s, "\n");
	
	
	seq_printf(s, "MIB_TABLES:\n");

	for (i = 0; i < 4; i++) {
		seq_printf(s, "\tWAN_RX_MIB_TABLE(%d): %d bytes\n", i, WAN_RX_MIB_TABLE(i)->wrx_total_bytes);
	}
	seq_printf(s, "\n");
	for (i = 0; i < 8; i++) {
		seq_printf(s, "\tWAN_TX_MIB_TABLE(%d): %d pkts (%d bytes)\n", i, WAN_TX_MIB_TABLE(i)->wtx_total_pdu, WAN_TX_MIB_TABLE(i)->wtx_total_bytes);
	}

	seq_printf(s, "\n");
	for (i = 0; i < 8; i++) {
		seq_printf(s, "\tITF_MIB_TBL(%d): %d\n", i, ITF_MIB_TBL(i)->ig_cpu_bytes);
	}


	return 0;
}

static int ltq_hal_proc_write_dbg(struct file *file, const char __user *buf, size_t count, loff_t *data)
{
	return 0;
}


static int ltq_hal_proc_read_dbg_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file, ltq_hal_debugfs_cfg1_show, NULL);
}

static struct proc_ops g_ltq_hal_proc_dbg_seq_fops = {
    .proc_open       = ltq_hal_proc_read_dbg_seq_open,
    .proc_read       = seq_read,
    .proc_write      = ltq_hal_proc_write_dbg,
    .proc_lseek     = seq_lseek,
    .proc_release    = single_release,
};


static void ltq_hal_init_debugfs(void)
{
	struct proc_dir_entry *res;

	g_ltq_hal_debugfs_dir = debugfs_create_dir(THIS_MODULE->name, NULL);

#if 0
	debugfs_create_devm_seqfile(NULL, "ltq_hal", g_ltq_hal_debugfs_dir,
				    ltq_hal_debugfs_cfg1_show);
#else

	res = proc_create("ltq_hal_cfg1", S_IRUGO|S_IWUSR, 0,
				&g_ltq_hal_proc_dbg_seq_fops);
	printk("res = %p\n", res);

#endif
}

int init_module(void)
{
	int i;
	printk(KERN_INFO "ltq-hal v0.1 init\n");

	ltq_hal_init_debugfs();

	printk(KERN_INFO "family: 0x%X, package: 0x%X, major: 0x%X, middle: 0x%X, minor: 0x%X\n", FW_VER_ID->family, FW_VER_ID->package, FW_VER_ID->major, FW_VER_ID->middle, FW_VER_ID->minor);
	printk(KERN_INFO "lan_acc_en: %d, wan_acc_en: %d\n", GEN_MODE_CFG->lan_acc_en, GEN_MODE_CFG->wan_acc_en);

	for (i = 0; i < 8; i++) {
		printk(KERN_INFO "MTU_CFG_TBL(%d): %u\n", i, (unsigned int)MTU_CFG_TBL(i));
	}

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

void cleanup_module(void)
{
	if (g_ltq_hal_debugfs_dir)
		debugfs_remove(g_ltq_hal_debugfs_dir);

	remove_proc_entry("ltq_hal_cfg1", NULL);

	printk(KERN_INFO "ltq-hal v0.1 exit\n");
}

MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
