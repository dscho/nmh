
/*
 * readconfig.c -- base routine to read nmh configuration files
 *              -- such as nmh profile, context file, or mhn.defaults.
 *
 * This code is Copyright (c) 2002, by the authors of nmh.  See the
 * COPYRIGHT file in the root directory of the nmh distribution for
 * complete copyright information.
 */

#include <h/mh.h>
#include <h/utils.h>

struct procstr {
    char *procname;
    char **procnaddr;
};

static struct procstr procs[] = {
    { "context",       &context },
    { "mh-sequences",  &mh_seq },
    { "buildmimeproc", &buildmimeproc },
    { "fileproc",      &fileproc },
    { "formatproc",    &formatproc },
    { "incproc",       &incproc },
    { "lproc",         &lproc },
    { "mailproc",      &mailproc },
    { "mhlproc",       &mhlproc },
    { "moreproc",      &moreproc },
    { "mshproc",       &mshproc },
    { "packproc",      &packproc },
    { "postproc",      &postproc },
    { "rmmproc",       &rmmproc },
    { "sendproc",      &sendproc },
    { "showmimeproc",  &showmimeproc },
    { "showproc",      &showproc },
    { "vmhproc",       &vmhproc },
    { "whatnowproc",   &whatnowproc },
    { "whomproc",      &whomproc },
    { NULL,            NULL }
};

static struct node **opp = NULL;


void
readconfig (struct node **npp, FILE *ib, char *file, int ctx)
{
    register int state;
    register char *cp;
    char name[NAMESZ], field[BUFSIZ];
    register struct node *np;
    register struct procstr *ps;
    m_getfld_state_t gstate = 0;

    if (npp == NULL && (npp = opp) == NULL) {
	admonish (NULL, "bug: readconfig called but pump not primed");
	return;
    }

    for (;;) {
	int fieldsz = sizeof field;
	switch (state = m_getfld (&gstate, name, field, &fieldsz, ib)) {
	    case FLD:
	    case FLDPLUS:
		np = (struct node *) mh_xmalloc (sizeof(*np));
		*npp = np;
		*(npp = &np->n_next) = NULL;
		np->n_name = getcpy (name);
		if (state == FLDPLUS) {
		    cp = getcpy (field);
		    while (state == FLDPLUS) {
			fieldsz = sizeof field;
			state = m_getfld (&gstate, name, field, &fieldsz, ib);
			cp = add (field, cp);
		    }
		    np->n_field = trimcpy (cp);
		    free (cp);
		} else {
		    np->n_field = trimcpy (field);
		}
		np->n_context = ctx;

		/*
		 * Now scan the list of `procs' and link in the
		 * field value to the global variable.
		 */
		for (ps = procs; ps->procname; ps++)
		    if (strcmp (np->n_name, ps->procname) == 0) {
			*ps->procnaddr = np->n_field;
			break;
		    }
		continue;

	    case BODY:
		adios (NULL, "no blank lines are permitted in %s", file);

	    case FILEEOF:
		break;

	    default:
		adios (NULL, "%s is poorly formatted", file);
	}
	break;
    }
    m_getfld_state_destroy (&gstate);

    /*
     * Special handling for the pager processes: lproc and moreproc.
     *
     * If they are not set by the profile, use the callers $PAGER if
     * available, otherwise set them to DEFAULT_PAGER.
     */
    if (lproc == NULL) {
        lproc = getenv("PAGER");
	if (lproc == NULL || lproc[0] == '\0')
	    lproc = DEFAULT_PAGER;
    }
    if (moreproc == NULL) {
        moreproc = getenv("PAGER");
	if (moreproc == NULL || moreproc[0] == '\0')
	    moreproc = DEFAULT_PAGER;
    }

    if (opp == NULL) {
	/* Check for duplicated non-null profile entries.  Except
	   allow multiple profile entries named "#", because that's
	   what the mh-profile man page suggests using for comments.

	   Only do this check on the very first call from
	   context_read(), when opp is NULL.  That way, entries in
	   mhn.defaults can be overridden without triggering
	   warnings.

	   Note that that mhn.defaults, $MHN, $MHBUILD, $MHSHOW, and
	   $MHSTORE all put their entries into just one list, m_defs,
	   the same list that the profile uses. */

	struct node *np;
	for (np = m_defs; np; np = np->n_next) {
	    /* Yes, this is O(N^2).  The profile should be small enough so
	       that's not a performance problem. */
	    if (strlen (np->n_name) > 0	 &&  strcmp ("#", np->n_name)) {
		struct node *np2;
		for (np2 = np->n_next; np2; np2 = np2->n_next) {
		    if (! strcasecmp (np->n_name, np2->n_name)) {
			admonish (NULL, "multiple \"%s\" profile components "
					"in %s, ignoring \"%s\"",
				  np->n_name, defpath, np2->n_field);
		    }
		}
	    }
	}
    }

    opp = npp;
}


void
add_profile_entry (const char *key, const char *value) {
    struct node *newnode = (struct node *) mh_xmalloc (sizeof *newnode);

    /* This inserts the new node at the beginning of m_defs because
       that doesn't require traversing it or checking to see if it's
       empty. */
    newnode->n_name = getcpy (key);
    newnode->n_field = getcpy (value);
    newnode->n_context = 0;
    newnode->n_next = m_defs;
    m_defs = newnode;
}
