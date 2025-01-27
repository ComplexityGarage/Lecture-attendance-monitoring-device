<template>
    <Head title="Dashboard" />

    <AuthenticatedLayout>
        <template #header>
            <h2 class="text-xl font-semibold leading-tight text-gray-800">
                Dashboard
            </h2>
        </template>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
            <div class="bg-white rounded-md shadow overflow-x-auto p-5">
                Attendance: {{ visitList.length }}
            </div>
        </div>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
            <div class="bg-white rounded-md shadow overflow-x-auto">
                <table class="w-full whitespace-nowrap">
                    <thead>
                        <tr class="text-left font-bold">
                            <th class="pb-4 pt-6 px-6">ID</th>
                            <th class="pb-4 pt-6 px-6">Hash</th>
                            <th class="pb-4 pt-6 px-6">Name</th>
                            <th class="pb-4 pt-6 px-6">Date</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr
                            v-for="visit in visitList"
                            :key="visit.id"
                            class="hover:bg-gray-100 focus-within:bg-gray-100"
                        >
                            <td class="border-t p-5 font-bold">
                                {{ visit.id }}
                            </td>
                            <td class="border-t p-5">
                                {{ visit.hash }}
                            </td>
                            <td class="border-t p-5">-</td>
                            <td class="w-px border-t p-5">
                                {{ visit.created_at }}
                            </td>
                        </tr>
                        <tr v-if="visitList.length === 0">
                            <td class="px-6 py-4 border-t" colspan="4">
                                No visits found.
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </AuthenticatedLayout>
</template>

<script>
import AuthenticatedLayout from "@/Layouts/AuthenticatedLayout.vue";
import { Head } from "@inertiajs/vue3";

export default {
    components: {
        AuthenticatedLayout,
        Head,
    },

    props: {
        visits: Object,
    },

    data: () => ({
        visitList: [],
    }),

    created() {
        Echo.private(`visits`).listen("VisitCreated", (e) => {
            this.visitList.unshift(e.visit);
        });
    },

    mounted() {
        this.visitList = [...this.visits.data];
    },
};
</script>
